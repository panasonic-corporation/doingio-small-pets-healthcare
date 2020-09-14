#ifndef UIGRAPHVIEW_H
#define UIGRAPHVIEW_H

#include "Config.h"
#include "UICellModel.h"
#include <M5Stack.h>

class UIGraphView
{
private:
    UICellModel *uiCellModelRef;

public:
    void setup(UICellModel *_uiCellModelRef);
    void draw();
};

#endif
