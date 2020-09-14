#include "UIGraphView.h"

void UIGraphView::setup(UICellModel *_uiCellModelRef)
{
    uiCellModelRef = _uiCellModelRef;
}

void UIGraphView::draw()
{
    int channel = uiCellModelRef -> channel;

    //[NUMBER_OF_SENSOR][channel][background(x, y, w, h)]
    int backgroundParamArray[6][6][4] = {{{14, 138, 293, 88},{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}},
                                        {{13, 155, 138, 71},{169, 155, 138, 71},{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}},
                                        {{211, 47, 97, 41},{211, 116, 97, 41},{211, 186, 97, 41},{0, 0, 0, 0},{0, 0, 0, 0},{0, 0, 0, 0}},
                                        {{218, 36, 91, 32},{218, 88, 91, 32},{218, 140, 91, 32},{218, 192, 91, 32},{0, 0, 0, 0},{0, 0, 0, 0}},
                                        {{86, 45, 68, 45},{86, 114, 68, 45},{86, 185, 68, 45},{242, 45, 68, 45},{242, 114, 68, 45},{0, 0, 0, 0}},
                                        {{86, 45, 68, 45},{86, 114, 68, 45},{86, 185, 68, 45},{242, 45, 68, 45},{242, 114, 68, 45},{242, 185, 68, 45}}};

    int bgX = backgroundParamArray[NUMBER_OF_SENSOR - 1][channel][0];
    int bgY = backgroundParamArray[NUMBER_OF_SENSOR - 1][channel][1];
    float bgW = backgroundParamArray[NUMBER_OF_SENSOR - 1][channel][2];
    float bgH = backgroundParamArray[NUMBER_OF_SENSOR - 1][channel][3];

    int lineDist = bgW / 6;

    int graphX[7];
    int graphY[7];

    int color = WHITE;
    //color = BLACK; //debug
    M5.Lcd.fillRect(bgX - 3, bgY - 3, (int)bgW + 6, (int)bgH + 6, color);
    M5.Lcd.fillRoundRect(bgX, bgY, (int)bgW, (int)bgH, 5, 0xf7be);
    for (int i = 1; i <= 5; i++) {
        M5.Lcd.drawFastVLine(bgX + lineDist * i, bgY, bgH, WHITE);
    }

    for (int i = 0; i <= 6; i++) {
        graphX[i] = bgX + lineDist * i;
    }

    int graphBottom = bgY + bgH;

    float graphMins[6] = {CH1_GRAPH_MIN, CH2_GRAPH_MIN, CH3_GRAPH_MIN, CH4_GRAPH_MIN, CH5_GRAPH_MIN, CH6_GRAPH_MIN};
    float graphMaxs[6] = {CH1_GRAPH_MAX, CH2_GRAPH_MAX, CH3_GRAPH_MAX, CH4_GRAPH_MAX, CH5_GRAPH_MAX, CH6_GRAPH_MAX};

    int graphMin = graphMins[channel];
    int graphMax = graphMaxs[channel];

    float graphStd = bgH / (graphMax - graphMin);

    for (int i = 0; i < 7; i++) 
    {
        if(uiCellModelRef -> displayDataRef -> displayWeekly[i].sensorsValue[channel] > SENSOR_VALUE_NULL)
        {
            graphY[i] = graphBottom - (int)(graphStd * (uiCellModelRef -> displayDataRef -> displayWeekly[i].sensorsValue[channel] - graphMin + 0.5));

        }else
        {
           graphY[i] = graphBottom; 
        }
        
    }

    for(int i = 0; i < 6; i++)
    {
        if(uiCellModelRef -> displayDataRef -> displayWeekly[i+1].sensorsValue[channel] > SENSOR_VALUE_NULL) //取得値がNULLじゃ
        {
            if(uiCellModelRef -> displayDataRef -> displayWeekly[i].sensorsValue[channel] > SENSOR_VALUE_NULL) //取得値がNULLじゃ
            {
                M5.Lcd.drawLine(graphX[i], graphY[i], graphX[i + 1], graphY[i + 1], RED);
            }
        }
    }
    
    if (uiCellModelRef -> displayDataRef -> isToday == false) {
        int circlePlace = uiCellModelRef -> displayDataRef -> displayDate.tm_wday;
        M5.Lcd.fillCircle(graphX[circlePlace], graphY[circlePlace], 2, RED);
    }
}
