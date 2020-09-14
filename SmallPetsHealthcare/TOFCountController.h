#include "VL53L0X.h"

#ifndef TOFCOUNTCONTROLLER_H
#define TOFCOUNTCONTROLLER_H

#include "DayDataModel.h"

class TOFCountController {
  private:
    DayDataModel *nowDayDataRef;
    VL53L0X sensor;

    int channel;
    int thresholdMin;
    int thresholdMax;

    int count = 0;
    bool beforeState;

  public:
    void setup(DayDataModel *_nowDayDataRef, int _channel, int _thresholdMin, int _thresholdMax);
    void update();
    void reset();
};

#endif
