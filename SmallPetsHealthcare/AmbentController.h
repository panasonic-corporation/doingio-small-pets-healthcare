
#ifndef AMBENTCONTROLLER_H
#define AMBENTCONTROLLER_H

#include <M5Stack.h>
#include <WiFi.h>
#include <Ambient.h>
#include "DayDataModel.h"

class AmbentController
{
private:
  DayDataModel *dayDataRef;
  Ambient ambient;
  bool isEnable = true;
public:
  void setup(DayDataModel *_dayDataRef, int channelid, char *writekey, WiFiClient *wclient);
  void send();
};
#endif
