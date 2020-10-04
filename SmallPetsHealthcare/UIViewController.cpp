#include "UIViewController.h"



void UIViewController::setup(DayDataModel *_nowDayDataRef)
{

    nowDayDataRef = _nowDayDataRef;

    displayDataController.setup(nowDayDataRef, &displayData);

    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.fillRoundRect(5, 26, 310, 209, 5, WHITE);

    uiHeader.setup(&displayData);


    UICellModel m;

    m.nowDayDataRef = _nowDayDataRef;
    m.displayDataRef = &displayData;

    m.title = CH1_TITLE;
    m.channel = CH1;
    m.valueIsInt = true;
    m.fgm.min = CH1_FG_MIN;
    m.fgm.max = CH1_FG_MAX;
    m.fsm.min = CH1_FS_MIN;
    m.fsm.max = CH1_FS_MAX;
    m.gm.min = CH1_GRAPH_MIN;
    m.gm.max = CH1_GRAPH_MAX;

    uiCells[CH1].setup(m);

    m.title = CH2_TITLE;
    m.channel = CH2;
    m.valueIsInt = true;
    m.fgm.min = CH2_FG_MIN;
    m.fgm.max = CH2_FG_MAX;
    m.fsm.min = CH2_FS_MIN;
    m.fsm.max = CH2_FS_MAX;
    m.gm.min = CH2_GRAPH_MIN;
    m.gm.max = CH2_GRAPH_MAX;
    uiCells[CH2].setup(m);

    m.title = CH3_TITLE;
    m.channel = CH3;
    m.valueIsInt = false;
    m.fgm.min = CH3_FG_MIN;
    m.fgm.max = CH3_FG_MAX;
    m.fsm.min = CH3_FS_MIN;
    m.fsm.max = CH3_FS_MAX;
    m.gm.min = CH3_GRAPH_MIN;
    m.gm.max = CH3_GRAPH_MAX;
    uiCells[CH3].setup(m);

    m.title = CH4_TITLE;
    m.channel = CH4;
    m.valueIsInt = true;
    m.fgm.min = CH4_FG_MIN;
    m.fgm.max = CH4_FG_MAX;
    m.fsm.min = CH4_FS_MIN;
    m.fsm.max = CH4_FS_MAX;
    m.gm.min = CH4_GRAPH_MIN;
    m.gm.max = CH4_GRAPH_MAX;
    uiCells[CH4].setup(m);

    m.title = CH5_TITLE;
    m.channel = CH5;
    m.valueIsInt = true;
    m.fgm.min = CH5_FG_MIN;
    m.fgm.max = CH5_FG_MAX;
    m.fsm.min = CH5_FS_MIN;
    m.fsm.max = CH5_FS_MAX;
    m.gm.min = CH5_GRAPH_MIN;
    m.gm.max = CH5_GRAPH_MAX;
    uiCells[CH5].setup(m);

    m.title = CH6_TITLE;
    m.channel = CH6;
    m.valueIsInt = true;
    m.fgm.min = CH6_FG_MIN;
    m.fgm.max = CH6_FG_MAX;
    m.fsm.min = CH6_FS_MIN;
    m.fsm.max = CH6_FS_MAX;
    m.gm.min = CH6_GRAPH_MIN;
    m.gm.max = CH6_GRAPH_MAX;
    uiCells[CH6].setup(m);




    switch (NUMBER_OF_SENSOR) {
        case 1:
            break;
        case 2:
            M5.Lcd.fillRect(160, 24, 2, 211, 0x0881);

            break;
        case 3:
            M5.Lcd.fillRect(0, 96, 315, 2, 0x0881);
            M5.Lcd.fillRect(0, 165, 315, 2, 0x0881);
            break;
        case 4:
            M5.Lcd.fillRect(0, 77, 315, 2, 0x0881);
            M5.Lcd.fillRect(0, 130, 315, 2, 0x0881);
            M5.Lcd.fillRect(0, 182, 315, 2, 0x0881);

            break;
        case 5:
            M5.Lcd.fillRect(160, 24, 2, 211, 0x0881);
            M5.Lcd.fillRect(0, 96, 315, 2, 0x0881);
            M5.Lcd.fillRect(0, 165, 315, 2, 0x0881);

            break;
        case 6:
            M5.Lcd.fillRect(160, 24, 2, 211, 0x0881);
            M5.Lcd.fillRect(0, 96, 315, 2, 0x0881);
            M5.Lcd.fillRect(0, 165, 315, 2, 0x0881);
            break;
    }

}

void UIViewController::update()
{
    if (M5.BtnA.wasPressed()) {
        displayDataController.prevDate();
        
        for (int i = 0; i < NUMBER_OF_SENSOR; i++) {
            uiCells[i].updateGraf();
        }


    }

    if (M5.BtnB.wasPressed()) {
        displayDataController.today();

        for (int i = 0; i < NUMBER_OF_SENSOR; i++) {
            uiCells[i].updateGraf();
        }
    }

    if (M5.BtnC.wasPressed()) {
        displayDataController.nextDate();

        for (int i = 0; i < NUMBER_OF_SENSOR; i++) {
            uiCells[i].updateGraf();
        }
    }
}

void UIViewController::draw()
{
    uiHeader.draw();
    for (int i = 0; i < NUMBER_OF_SENSOR; i++) {
        uiCells[i].draw();
    }
 }

void UIViewController::saveLogData()
{
    displayDataController.saveLogData();
}

void UIViewController::reload()
{
    if(displayData.isToday == true)//表示が今日ならば表示更新
    {
        displayDataController.today();
        for (int i = 0; i < NUMBER_OF_SENSOR; i++) {
            uiCells[i].updateGraf();
        }
    }
}