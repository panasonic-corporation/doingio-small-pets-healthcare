#ifndef UICELLVIEW_H
#define UICELLVIEW_H

#include "Config.h"
#include "UIGraphView.h"
#include "UIFaceView.h"
#include "UICellModel.h"
#include <M5Stack.h>

class UICellView
{
private:
    UICellModel uiCellModel;
    UIFaceView uiFaceView;
    UIGraphView uiGraphView;
    float beforeSensorValue;

    void drawTitle(String _title);
    void drawValue(float _value, bool _valueIsInt);
    void drawRect();
    
public:
    void setup(UICellModel _uiCellModel);
    void updateGraf();
    void draw();
};

#endif
