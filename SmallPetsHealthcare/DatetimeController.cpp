#include "DatetimeController.h"

void DatetimeController::setup(DayDataModel *_nowDayDataRef )
{
    nowDayDataRef  = _nowDayDataRef ;
    // NTPサーバ設定
    configTime(gmtOffsetSec, daylightOffset, ntpServer);
    while (!getLocalTime(&timeInfo)) {
        delay(1000);
    }
    update();
}

void DatetimeController::update()
{
    getLocalTime(&timeInfo);
    nowDayDataRef  -> nowtimeInfo = timeInfo;
}
