#include "TwitterController.h"
#include "config.h"

void TwitterController::setup(DayDataModel *_nowDayDataRef, char *_token) {
  nowDayDataRef = _nowDayDataRef;
  if(strcmp(_token, "")!=0)
  {
    wifitwitterRef = new WifiTwitter(_token);
  }else
  {
    isEnable = false;
  }
}

void TwitterController::tweet() {
  if(!isEnable) return;
  
  Serial.print("tweet: ");

  String title[6] = {CH1_TITLE, CH2_TITLE, CH3_TITLE, CH4_TITLE, CH5_TITLE, CH6_TITLE};

  int year = nowDayDataRef -> nowtimeInfo.tm_year + 1900;
  int month = nowDayDataRef -> nowtimeInfo.tm_mon + 1;
  int day = nowDayDataRef -> nowtimeInfo.tm_mday;
  int hour = nowDayDataRef -> nowtimeInfo.tm_hour;
  int min = nowDayDataRef -> nowtimeInfo.tm_min;

  char buf[128];
  sprintf(buf, "%04d/%02d/%02d %02d:%02d ", year, month, day, hour, min);
  String tweetStr = buf;

  for(int i = 0; i < NUMBER_OF_SENSOR; i++) {
    tweetStr += title[i] + ": ";
    tweetStr += nowDayDataRef->sensorsValue[i];
    tweetStr += ", ";
  }

  Serial.println(tweetStr);

  if (wifitwitterRef->post(tweetStr.c_str())) {

     Serial.print(" post: ");

     if(wifitwitterRef->checkStatus())
     {
       Serial.println("OK.");
     }else
     {
       Serial.println("error.");
     }
     
  } else {
    Serial.println("connection failed.");
  }
  

}
