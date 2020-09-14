#ifndef UIFACEVIEW_H
#define UIFACEVIEW_H

//#include "UIViewController.h"
#include "Config.h"
#include "UICellModel.h"
#include <M5Stack.h>

class UIFaceView
{
private:
    float value;
    UICellModel *uiCellModelRef;

public:
    void setup(UICellModel *_uiCellModelRef);
    void setValue(float _value);
    void draw();
};

#endif
