#ifndef DATEDATAMODEL_H
#define DATEDATAMODEL_H

#include "DayDataModel.h"
#include <M5Stack.h>

class DisplayDataModel
{
public:
    struct tm displayDate;
    bool isToday;
    DayDataModel displayWeekly[7];
    bool isLatestWeek;
    bool isCheck;
};

#endif
