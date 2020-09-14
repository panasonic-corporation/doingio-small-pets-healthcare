#ifndef UIVIEWCONTROLLER_H
#define UIVIEWCONTROLLER_H

#include "Config.h"
#include "DayDataModel.h"
#include "UICellView.h"
#include "UIHeaderView.h"
#include "DateDataController.h"
#include "UICellModel.h"
#include "DisplayDataModel.h"
#include <M5Stack.h>
#include <CSV_Parser.h>

class UIViewController
{
private:
    UIHeaderView uiHeader;
    UICellView uiCells[6];
    DayDataModel *nowDayDataRef;
    DisplayDataModel displayData; 

    DateDataController displayDataController;

public:
    void setup(DayDataModel *_nowDayDataRef);
    void update();
    void draw();
    void saveLogData();
    void reload();
};

#endif
