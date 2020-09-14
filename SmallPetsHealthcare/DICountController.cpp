#include "Arduino.h"
#include "DICountController.h"
#include "Config.h"

void DICountController::setup(DayDataModel *_nowDayDataRef, int _channel, int _dataPin, int _lowPin, int _timeChat) {
  nowDayDataRef = _nowDayDataRef;
  staticNowDataRef = _nowDayDataRef;
  channel = _channel;
  timeChat = _timeChat;
  dataPin = _dataPin;
  lowPin = _lowPin;

  interruptDICountBuf = nowDayDataRef->sensorsValue[channel];
  
  if(channel > NOCH)
  {
    pinMode(dataPin, INPUT_PULLUP);
    pinMode(lowPin, OUTPUT);
    digitalWrite(lowPin, LOW);

    char DIPin = digitalPinToInterrupt(dataPin);
    attachInterrupt(dataPin, interruptDI, FALLING);
  }
}

void DICountController::update() {
  nowDayDataRef->sensorsValue[channel] = interruptDICountBuf;

    //debug output
    Serial.print("DICount count: ");
    Serial.println (interruptDICountBuf);

}

void DICountController::reset() {
  interruptDICountBuf = 0;
}

void interruptDI() {
  timeNow = millis();
  if ( timeNow - timePre > timeChat) {
    interruptDICountBuf++;
  }
  timePre = timeNow;
}
