#include "MotionCountController.h"
#include "Config.h"

void MotionCountController::setup(DayDataModel *_nowDayDataRef, int _channel, int _pin) {
  nowDayDataRef = _nowDayDataRef;
  channel = _channel;

  beforePinState = false;
  pin = _pin;
  
  motionTimeMsec = nowDayDataRef->sensorsValue[channel] * 60000;

  if(channel > NOCH)
    pinMode(pin, INPUT);
}

void MotionCountController::update() {

  if(channel > NOCH)
  {
    bool pinState = digitalRead(pin);
    if(pinState && !beforePinState){
      beforePinState = true;

      pinUpTime = millis();
      
    } else if(!pinState && beforePinState) {
      beforePinState = false;

      pinDownTime = millis();
      motionTimeMsec += (pinDownTime - pinUpTime);

    }

    nowDayDataRef->sensorsValue[channel] = (int)motionTimeMsec / 60000;

    //debug output
    Serial.print("Motion pin: ");
    Serial.print(pinState);
    Serial.print (", msec: ");
    Serial.println (motionTimeMsec);

  }
}

void MotionCountController::reset() {
  pinUpTime = 0;
  pinDownTime = 0;
  motionTimeMsec = 0;
}
