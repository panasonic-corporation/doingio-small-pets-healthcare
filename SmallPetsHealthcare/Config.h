#ifndef CONFIG_H
#define CONFIG_H


// ネットワーク系設定値 ///////////////////////////////////////////////////////

// WiFi設定値 (必須！wifiがないと起動しません。D+IO画面で止まったままになります) 
#define WIFI_SSID "SSID"
#define WIFI_PASSWD "PASSWD"

// ambidata.io設定値
#define AMBIDATA_CH_ID -1 // AmbientのチャネルID 連携しない場合は-1を設定
#define AMBIDATA_WRITEKEY "" // ライトキー

//　Tweet Library for Arduino設定値 
#define TW_TOKEN "" //連携しない場合は""に設定



// UI表示設定値 ///////////////////////////////////////////////////////////

//表示レイアウト(1...6)
#define NUMBER_OF_SENSOR 6

//表示チャンネル1設定値
#define CH1 0               //表示チャネルインデックス(変更不可)
#define CH1_TITLE "WEIGHT(g)"  //表示チャンネルのタイトル
#define CH1_GRAPH_MIN 0     //表示チャンネルグラフの最小値
#define CH1_GRAPH_MAX 200   //表示チャンネルグラフの最大
#define CH1_FS_MIN 10       //値によるFaceIcon閾値 SOSO範囲の最小　
#define CH1_FS_MAX 75       //値によるFaceIcon閾値 SOSO範囲の最大
#define CH1_FG_MIN 30       //値によるFaceIcon閾値 GOOD範囲の最小
#define CH1_FG_MAX 45       //値によるFaceIcon閾値 GOOD範囲の最大 それ以外はBAD値

//表示チャンネル2設定値
#define CH2 1
#define CH2_TITLE "ACTIVE(min)"
#define CH2_GRAPH_MIN 0
#define CH2_GRAPH_MAX 500
#define CH2_FS_MIN 5
#define CH2_FS_MAX 100
#define CH2_FG_MIN 100
#define CH2_FG_MAX 99999

//表示チャンネル3設定
#define CH3 2
#define CH3_TITLE "TEMPERATURE(°c)"
#define CH3_GRAPH_MIN 0.0
#define CH3_GRAPH_MAX 50.0
#define CH3_FS_MIN 15
#define CH3_FS_MAX 28
#define CH3_FG_MIN 20
#define CH3_FG_MAX 26

//表示チャンネル4設定値
#define CH4 3
#define CH4_TITLE "WHEEL(x)"
#define CH4_GRAPH_MIN 0
#define CH4_GRAPH_MAX 50000
#define CH4_FS_MIN 1000
#define CH4_FS_MAX 2000
#define CH4_FG_MIN 2000
#define CH4_FG_MAX 99999

//表示チャンネル5設定値
#define CH5 4
#define CH5_TITLE "HOUSE(x)"
#define CH5_GRAPH_MIN 0
#define CH5_GRAPH_MAX 2000
#define CH5_FS_MIN 5
#define CH5_FS_MAX 20
#define CH5_FG_MIN 20
#define CH5_FG_MAX 99999

//表示チャンネル6設定値
#define CH6 5
#define CH6_TITLE "HUM"
#define CH6_GRAPH_MIN 0
#define CH6_GRAPH_MAX 100
#define CH6_FS_MIN 40
#define CH6_FS_MAX 75
#define CH6_FG_MIN 45
#define CH6_FG_MAX 60



// センサー 定数 //////////////////////////////////////////////////////////

// WEIGHTセンサー設定値
#define WEIGHT_DOUT_PIN 36
#define WEIGHT_SLK_PIN 17
#define WEIGHT_THRESHOLD 10.0f
#define WEIGHT_OUTVOL 0.001f
#define WEIGHT_LOAD 1000.0f
#define WEIGHT_CALIB 1.18
#define WEIGHT_FIL 256

// HOUSE(TOF)センサー設定値
#define HOME_THRESHOLD_MIN 80
#define HOME_THRESHOLD_MAX 120

// WHEEL(ドア)センサー設定値
#define WHEEL_PIN1 3
#define WHEEL_PIN2 16
#define WHEEL_TIMECHAT 100

// ACTIVE(モーション)センサー設定値
#define MOTION_PIN 35







// 各ファイルパス ////////////////////////////////////////////////////////

#define LOG_PATH "/SD/log.csv"
#define TEMPDATA_PATH "/SD/tmp.csv"
#define FONT1 "/SD/fonts/Montserrat-Regular12"
#define FONT2 "/SD/fonts/Montserrat-Medium14"
#define FONT3 "/SD/fonts/Montserrat-Regular15"
#define FONT4 "/SD/fonts/Montserrat-Regular18"
#define FONT5 "/SD/fonts/Montserrat-Regular20"
#define FONT6 "/SD/fonts/Montserrat-Regular26"
#define FONT7 "/SD/fonts/Montserrat-Regular33"
#define FONT8 "/SD/fonts/Montserrat-Regular38"
#define FONT9 "/SD/fonts/Montserrat-Regular53"
#define WIFIICON_PATH "/SD/images/Frame.png"
#define LOGO_IMAGE "/SD/images/logo.png"

// 各定数(変更不可) ////////////////////////////////////////////////////////////
#define SENSOR_VALUE_NULL -9999.9
#define NOCH -1

#endif
