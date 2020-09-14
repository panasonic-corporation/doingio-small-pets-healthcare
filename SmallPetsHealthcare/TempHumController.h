#include "SHT3X.h"

#ifndef TEMPHUMCONTROLLER_H
#define TEMPHUMCONTROLLER_H

#include "DayDataModel.h"

class TempHumController {
  private:
    DayDataModel *nowDayDataRef;
    SHT3X sht30;

    float temp = 0.0;
    float hum = 0.0;
    int tempChannel, humChannel;

  public:
    void setup(DayDataModel *_nowDayDataRef, int _tempChannel, int _humChannel);
    void update();
    void rest();
};
#endif