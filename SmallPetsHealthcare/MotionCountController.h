#include "Arduino.h"

#ifndef MOTIONCOUNTCONTROLLER_H
#define MOTIONCOUNTCONTROLLER_H

#include "DayDataModel.h"

class MotionCountController {
  private:
    DayDataModel *nowDayDataRef;

    int channel;
    int pin;
    bool beforePinState;

    long motionTimeMsec = 0;
    int pinUpTime;
    int pinDownTime;

  public:
    void setup(DayDataModel *_nowDayDataRef, int _channel, int _pin);
    void update();
    void reset();
};

#endif
