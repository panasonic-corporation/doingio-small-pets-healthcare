#include <M5Stack.h>
#include <WiFi.h>
#include <time.h>
#include "ClosedCube_TCA9548A.h"

#include "split.h"

//
#include "Config.h"
#include "DayDataModel.h"
#include "DatetimeController.h"
#include "UIViewController.h"
#include "TempHumController.h"
#include "WeightController.h"
#include "TOFCountController.h"
#include "DICountController.h"
#include "MotionCountController.h"
#include "AmbentController.h"
#include "TwitterController.h"

//Baseクラスをインスタンス化
ClosedCube::Wired::TCA9548A baHUB;
DayDataModel nowDayData;
DatetimeController datetimeController;
UIViewController uiViewController;



//センサークラスをインスタンス化
TempHumController tempHumController;
WeightController weightController;
TOFCountController houseCountController;
DICountController wheelCountController;
MotionCountController ActiveCountController;



//外部サービス連携クラスをインスタンス化
AmbentController ambientContrller;
TwitterController twitterController;

int beforeDay = -1;
int beforeHour = -1;
int beforeMin = -1;

WiFiClient client;

void setup() {
  M5.begin();
  Wire.begin();

  delay(500);
  Serial.begin(115200);

  //起動ロゴ表示
  M5.Lcd.drawPngFile(SD, LOGO_IMAGE);
  delay(1000);

  //WIFI起動
  Serial.println();
  Serial.println("wifi start");

  WiFi.begin(WIFI_SSID, WIFI_PASSWD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }
  if (WiFi.status() == WL_CONNECTED) {
    M5.Lcd.println("Connected");
    M5.Lcd.println(WiFi.localIP());
    
    Serial.println("Connected");
    Serial.println(WiFi.localIP());

  }

  Serial.println("setup start");

  dacWrite(25, 0); ///スピーカノイズ除去の呪文

  //ベースクラスをセットアップ
  datetimeController.setup(&nowDayData);
  uiViewController.setup(&nowDayData);

  beforeDay = nowDayData.nowtimeInfo.tm_mday;
  beforeHour = nowDayData.nowtimeInfo.tm_hour;
  beforeMin = nowDayData.nowtimeInfo.tm_min;

  //再起動やクラッシュに備えて保存したtempデータを読み込み
  loadTempData();


  //--センサークラスをセットアップ
  weightController.setup(&nowDayData, CH1, WEIGHT_DOUT_PIN, WEIGHT_SLK_PIN, WEIGHT_THRESHOLD, WEIGHT_OUTVOL, WEIGHT_LOAD, WEIGHT_CALIB);
  ActiveCountController.setup(&nowDayData, CH2, MOTION_PIN);
  tempHumController.setup(&nowDayData, CH3, CH6);
  wheelCountController.setup(&nowDayData, CH4, WHEEL_PIN1, WHEEL_PIN2, WHEEL_TIMECHAT);
  houseCountController.setup(&nowDayData, CH5, HOME_THRESHOLD_MIN, HOME_THRESHOLD_MAX);


  //外部連携クラスをセットアップ
  ambientContrller.setup(&nowDayData, AMBIDATA_CH_ID, AMBIDATA_WRITEKEY, &client);
  twitterController.setup(&nowDayData, TW_TOKEN); 
    
}



void loop() {
  m5.update();

  //ベースクラスをアップデート
  datetimeController.update();


  //--センサークラスをアップデート
  weightController.update();
  ActiveCountController.update();
  wheelCountController.update(); 
  
  paHUB_selectChannel(3); //PaHUBでI2Cを切り替え
  houseCountController.update();
  
  paHUB_selectChannel(5); //PaHUBでI2Cを切り替え
  tempHumController.update();




  //UIをアップデート＆描画
  uiViewController.update();
  uiViewController.draw();



  //１分おきに実行
  if(beforeMin!=nowDayData.nowtimeInfo.tm_min)
  {
    beforeMin = nowDayData.nowtimeInfo.tm_min;
    saveTempData(); //再起動、クラッシュに備えて定期的に値をバックアップ(temp)として保存
  }

  //１時間おきに実行
  if(beforeHour!=nowDayData.nowtimeInfo.tm_hour)
  {
    beforeHour = nowDayData.nowtimeInfo.tm_hour;
    ambientContrller.send();
    twitterController.tweet();
  }
  
  //１日おきに実行
  if(beforeDay!=nowDayData.nowtimeInfo.tm_mday)
  {
    beforeDay = nowDayData.nowtimeInfo.tm_mday;

    //１日のデータをログとして保存
    uiViewController.saveLogData();

    //各センサーの値をリセット
    weightController.reset();
    ActiveCountController.reset();
    tempHumController.rest();
    wheelCountController.reset();
    houseCountController.reset();
    uiViewController.reload();
  }


  delay(1);
}


void paHUB_selectChannel(int ch)
{
  //PaHUBでI2Cを切り替え
  baHUB.address(0x70);
  baHUB.selectChannel(ch); 
}

void loadTempData()
{
  //オートセーブの値を読み込み
  CSV_Parser cp("sffffff");

  File file = SD.open(TEMPDATA_PATH);
  if (file) {
      
      while(file.available()) {
          cp << file.read();
      }
      file.close();

      int len = cp.getRowsCount();

      Serial.print("temp len: ");    
      Serial.println(len);

      int c = 0;
      for(int i = len-1; i >= 0; i--)
      {
          char str[16];
          strcpy(str, ((char**)cp[0])[i]);
          char *dst[8];
          int count = split(dst, str, '/');
          if(count < 3)
          {
              Serial.print("date error: ");
              Serial.println(str);
              continue; //日付フォーマットではない
          } 

          struct tm  tinfo;
          memset(&tinfo, 0, sizeof(struct tm));
          tinfo.tm_year = (atoi(dst[0]) - 1900);
          tinfo.tm_mon = (atoi(dst[1]) - 1);
          tinfo.tm_mday = (atoi(dst[2]));


          nowDayData.nowtimeInfo = tinfo;
          nowDayData.sensorsValue[0] = ((float*)cp[1])[i];
          nowDayData.sensorsValue[1] = ((float*)cp[2])[i];
          nowDayData.sensorsValue[2] = ((float*)cp[3])[i];
          nowDayData.sensorsValue[3] = ((float*)cp[4])[i];
          nowDayData.sensorsValue[4] = ((float*)cp[5])[i];
          nowDayData.sensorsValue[5] = ((float*)cp[6])[i];
          c++;

          if(c >=1) break;
      }
  }
}
void saveTempData()
{
    char buf[128];
    sprintf(buf, "%04d/%02d/%02d,", nowDayData.nowtimeInfo.tm_year+1900, nowDayData.nowtimeInfo.tm_mon+1, nowDayData.nowtimeInfo.tm_mday);
    String str = buf;

    for(int i = 0; i < 6; i++) {
        str += nowDayData.sensorsValue[i];
        if(i<(6-1))
        {
            str += ",";
        }
    }
    
    str = "DATE,CH1,CH2,CH3,CH4,CH5,CH6\n" + str;
  
    Serial.print("saveTemp: ");
    Serial.println(str);

    File file = SD.open(TEMPDATA_PATH, FILE_WRITE);
    file.println(str);
    file.close();

}
