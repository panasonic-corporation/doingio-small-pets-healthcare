#include "AmbentController.h"

void AmbentController::setup(DayDataModel *_dayDataRef, int channelid, char *writekey, WiFiClient *wclient)
{
  dayDataRef = _dayDataRef;
  if(channelid >= 0)
  {
    Serial.print("ambient setup");
    const char* cwriteKey = writekey;
    int b = ambient.begin(channelid, cwriteKey, wclient);
    Serial.println(b);
  }else
  {
    isEnable = false;
  }
}

void AmbentController::send()
{
  if(!isEnable) return;
  Serial.print("ambient send:");
  ambient.set(1, dayDataRef->sensorsValue[0]);
  ambient.set(2, dayDataRef->sensorsValue[1]);
  ambient.set(3, dayDataRef->sensorsValue[2]);
  ambient.set(4, dayDataRef->sensorsValue[3]);
  ambient.set(5, dayDataRef->sensorsValue[4]);
  ambient.set(6, dayDataRef->sensorsValue[5]);
  bool b = ambient.send();
  Serial.println(b);

}
