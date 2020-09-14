#ifndef WEIGHTCONTROLLER_H
#define WEIGHTCONTROLLER_H

#include "B_HX711.h"
#include "DayDataModel.h"
#include "Config.h"

class WeightController {
  private:
    DayDataModel *nowDayDataRef;
    B_HX711 bhx711;

    int channel;
    float threshold;
    
    float weightArray[WEIGHT_FIL];
    int weightArrayIndex = 0;

  public:
    void setup(DayDataModel *_nowDayDataRef, int _channel, int _DOUT_PIN, int _SLK_PIN, float _threshold, float _OUTVOL, float _LOAD , float _CALIB);
    void update();
    void reset();
};
#endif