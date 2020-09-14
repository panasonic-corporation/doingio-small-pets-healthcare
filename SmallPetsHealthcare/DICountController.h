#include "Arduino.h"

#ifndef DICOUNTCONTROLLER_H
#define DICOUNTCONTROLLER_H

#include "DayDataModel.h"

class DICountController {
  private:
    DayDataModel *nowDayDataRef;

    int channel;
    int dataPin, lowPin;

  public:
    void setup(DayDataModel *_nowDayDataRef, int _channel, int _dataPin, int _lowPin, int _timeChat);
    void update();
    void reset();
};

static DayDataModel *staticNowDataRef;
static DICountController* anchor;

static void interruptDI();

static unsigned long timeNow;
static unsigned long timePre = 0;
static unsigned long timeChat = 20;
static volatile int interruptDICountBuf = 0;

#endif
