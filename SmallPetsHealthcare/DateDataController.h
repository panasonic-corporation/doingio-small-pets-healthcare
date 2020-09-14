#ifndef DATEDATACONTROLLER_H
#define DATEDATACONTROLLER_H

#include "Config.h"
//#include "UIViewController.h"
#include "DisplayDataModel.h"
#include <CSV_Parser.h>
#include <M5Stack.h>
#include <string.h>

typedef struct 
{
    int len;
    int seek;
    DayDataModel log[365];
}LogData, *LogDataRef;

class DateDataController
{
private:
    DayDataModel *nowDayDataRef;
    DisplayDataModel *dateDataRef;
    LogData logData;

    void loadLogData();
    void weekSeek(bool isUpSeek = false);

public:
    void setup(DayDataModel *_nowDayDataRef, DisplayDataModel *_dateDataRef);
    void nextDate();
    void prevDate();
    void today();
    void saveLogData();
    
};

#endif



