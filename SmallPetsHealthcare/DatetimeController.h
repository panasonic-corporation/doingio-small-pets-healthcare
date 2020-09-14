#ifndef DATETIMECONTROLLER_H
#define DATETIMECONTROLLER_H

#include <M5Stack.h>
#include <time.h>
#include "DayDataModel.h"

class DatetimeController
{
private:
    DayDataModel *nowDayDataRef ;
    
    const long gmtOffsetSec = 9 * 3600;
    const int daylightOffset = 0;
    const char* ntpServer = "ntp.jst.mfeed.ad.jp";
    struct tm timeInfo;

public:
    void setup(DayDataModel *_nowDayDataRef );
    void update();
};

#endif
