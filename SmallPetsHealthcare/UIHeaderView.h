#ifndef UIHEADER_H
#define UIHEADER_H

#include "Config.h"
#include "DisplayDataModel.h"
#include <M5Stack.h>

class UIHeaderView
{
private:
    DisplayDataModel *displayDataRef;

    bool beforeDispToday;
    String beforeDisplayDateString;

public:
    void setup(DisplayDataModel *_displayDataRef);
    void draw();
};

#endif
