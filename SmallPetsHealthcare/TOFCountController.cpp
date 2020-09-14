#include <Wire.h>
#include "TOFCountController.h"
#include "Config.h"

void TOFCountController::setup(DayDataModel *_nowDayDataRef, int _channel, int _thresholdMin, int _thresholdMax) {
  nowDayDataRef = _nowDayDataRef;
  channel = _channel;

  thresholdMin = _thresholdMin;
  thresholdMax = _thresholdMax;

  beforeState = false;

  count = nowDayDataRef->sensorsValue[channel];
}

void TOFCountController::update() {
  if(channel > NOCH)
  {
    sensor.init();
    sensor.setTimeout(50);
    int distance = sensor.readRangeSingleMillimeters();

    if(distance <= thresholdMin)
    {
      if(beforeState == false)
      {
        beforeState = true;
        count++;
      }
    }else if(distance >= thresholdMin)
    {
      if(beforeState == true) beforeState = false;
    }

    nowDayDataRef->sensorsValue[channel] = count;

    //debug output
    Serial.print("tof distance: ");
    Serial.print(distance);
    Serial.print (", count: ");
    Serial.println (count);

  }
}

void TOFCountController::reset() {
  count = 0;
}