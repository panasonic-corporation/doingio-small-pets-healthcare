#include <Wire.h>
#include "TempHumController.h"
#include "Config.h"

void TempHumController::setup(DayDataModel *_nowDayDataRef, int _tempChannel, int _humChannel) {
  nowDayDataRef = _nowDayDataRef;
  tempChannel = _tempChannel;
  humChannel = _humChannel;
}

void TempHumController::update() {
  if(tempChannel > NOCH || humChannel > NOCH)
  {
    if (sht30.get() == 0) {
      temp = sht30.cTemp;
      hum = sht30.humidity;
    }
    nowDayDataRef->sensorsValue[tempChannel] = temp;
    nowDayDataRef->sensorsValue[humChannel] = hum;

    //debug output
    Serial.print("TempHum temp: ");
    Serial.print(temp);
    Serial.print (", hum: ");
    Serial.println (hum);

  }

}

void TempHumController::rest() {
  
}
