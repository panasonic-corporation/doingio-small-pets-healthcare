#include "UICellView.h"

void UICellView::setup(UICellModel _uiCellModel)
{
    beforeSensorValue = SENSOR_VALUE_NULL;
    uiCellModel = _uiCellModel;
    uiFaceView.setup(&uiCellModel);
    uiGraphView.setup(&uiCellModel);

    uiGraphView.draw();
}

void UICellView::draw()
{
    
    String title = uiCellModel.title;

    int channel = uiCellModel.channel;
    int day = uiCellModel.displayDataRef->displayDate.tm_wday;

    float sensorValue = 0.0;
    if (uiCellModel.displayDataRef -> isToday) {
        sensorValue = uiCellModel.nowDayDataRef -> sensorsValue[channel];
    }
    else { 
        sensorValue = uiCellModel.displayDataRef -> displayWeekly[day].sensorsValue[channel];
    }
    
    int sv = (int)sensorValue;
    if(!uiCellModel.valueIsInt)
    {
        sv = (int)(sensorValue *10);
    }

    if(beforeSensorValue != sv)
    {

        beforeSensorValue = sv;
        drawRect();
        drawValue(sensorValue, uiCellModel.valueIsInt);
        uiFaceView.setValue(sensorValue);
        uiFaceView.draw();
        drawTitle(title);
    }
    
}

void UICellView::drawRect()
{
    //{x, y, w, h, yrow, ystep, xstep}
    const int rectValues[6][7] = {
        {5, 55, 310, 78, 1, 0, 0},
        {5, 52, 154, 98, 1, 0, 157},
        {5, 45, 203, 48, 3, 69, 0},
        {83, 28, 132, 48, 4, 52, 0},
        {5, 43, 79, 51, 3, 69, 157},
        {5, 43, 79, 51, 3, 69, 157}
    };
        
    int rectidx = NUMBER_OF_SENSOR - 1;
    int yy = uiCellModel.channel % rectValues[rectidx][4] * rectValues[rectidx][5];
    int xx = uiCellModel.channel / rectValues[rectidx][4] * rectValues[rectidx][6];

    int color = WHITE;
    //color = RED;//debug
    M5.Lcd.fillRect(rectValues[rectidx][0] +  xx, rectValues[rectidx][1] + yy, rectValues[rectidx][2], rectValues[rectidx][3], color);
}
void UICellView::drawTitle(String _title)
{
    const int titleXYArray[6][6][2] = {{{160, 37},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}},
                                {{82, 34},{238, 34},{0, 0},{0, 0},{0, 0},{0, 0}},
                                {{160, 32},{160, 102},{160, 172},{0, 0},{0, 0},{0, 0}},
                                {{42, 53},{42, 105},{42, 157},{42, 209},{0, 0},{0, 0}},
                                {{82, 31},{82, 101},{82, 170},{238, 31},{238, 101},{0, 0}},
                                {{82, 31},{82, 101},{82, 170},{238, 31},{238, 101},{238, 170}}};
    const String titleFontArray[6] = {FONT4, FONT3, FONT1, FONT1, FONT1, FONT1};
    const int titleDatumArray[6] = {1, 1, 1, 4, 1, 1};

    int channel = uiCellModel.channel;

    M5.Lcd.loadFont(titleFontArray[NUMBER_OF_SENSOR - 1], SD);
    M5.Lcd.setTextColor(0xad75, WHITE);
    M5.Lcd.setTextDatum(titleDatumArray[NUMBER_OF_SENSOR - 1]);
    M5.Lcd.drawString(_title, titleXYArray[NUMBER_OF_SENSOR - 1][channel][0], titleXYArray[NUMBER_OF_SENSOR - 1][channel][1]);
    M5.Lcd.unloadFont();
}


void UICellView::drawValue(float _value, bool _valueIsInt)
{
    const int dataXYArray[6][6][2] = {{{268, 72},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}},
                                 {{81, 108},{238, 108},{0, 0},{0, 0},{0, 0},{0, 0}},
                                 {{189, 68},{189, 137},{189, 207},{0, 0},{0, 0},{0, 0}},
                                 {{211, 53},{211, 105},{211, 157},{211, 209},{0, 0},{0, 0}},
                                 {{44, 81},{44, 150},{44, 221},{201, 81},{201, 150},{0, 0}},
                                 {{44, 81},{44, 150},{44, 221},{201, 81},{201, 150},{201, 221}}};
    const String valueFontArray[6] = {FONT9, FONT8, FONT7, FONT6, FONT5, FONT5};
    const int valueDatumArray[6] = {2, 1, 5, 5, 4, 4};
    
    int channel = uiCellModel.channel;

    M5.Lcd.loadFont(valueFontArray[NUMBER_OF_SENSOR - 1], SD);
    M5.Lcd.setTextColor(0xad75, WHITE);
    M5.Lcd.setTextDatum(valueDatumArray[NUMBER_OF_SENSOR - 1]);

    if (_value <= SENSOR_VALUE_NULL) {
        M5.Lcd.drawString("-", dataXYArray[NUMBER_OF_SENSOR - 1][channel][0], dataXYArray[NUMBER_OF_SENSOR - 1][channel][1]);
    }
    else if (_valueIsInt) {
        M5.Lcd.drawNumber(_value, dataXYArray[NUMBER_OF_SENSOR - 1][channel][0], dataXYArray[NUMBER_OF_SENSOR - 1][channel][1]);
    }
    else {
        float v = float((int)(_value * 10))/10.0;
        M5.Lcd.drawFloat(v, 1, dataXYArray[NUMBER_OF_SENSOR - 1][channel][0], dataXYArray[NUMBER_OF_SENSOR - 1][channel][1]);
    }

    M5.Lcd.unloadFont();

}

void UICellView::updateGraf()
{
    uiGraphView.draw();
}