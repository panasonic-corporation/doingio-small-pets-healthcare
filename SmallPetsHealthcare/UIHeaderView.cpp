#include "UIHeaderView.h"

void UIHeaderView::setup(DisplayDataModel *_displayDataRef)
{
    displayDataRef = _displayDataRef;
    beforeDispToday = false;
    beforeDisplayDateString = "";
}

void UIHeaderView::draw()
{
    String displayWeekDay[7] = {"Sun", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat"};

    bool dispToday = displayDataRef -> isToday;
    int displayYear = displayDataRef -> displayDate.tm_year + 1900;
    int displayMonth = displayDataRef -> displayDate.tm_mon + 1;
    int displayDay = displayDataRef -> displayDate.tm_mday;
    int displayWeekDayIndex = displayDataRef -> displayDate.tm_wday;

    char buf[128];
    sprintf(buf, "%04d.%02d.%02d %s", displayYear, displayMonth, displayDay,displayWeekDay[displayWeekDayIndex]);

    String displayDateString = buf;

    if(beforeDisplayDateString != displayDateString) //値が変わった時だけ更新
    {
        beforeDisplayDateString = displayDateString;

        M5.Lcd.fillRect(0, 0, 320, 21, 0x3186);
        M5.Lcd.drawPngFile(SD, WIFIICON_PATH, 299, 4, 0x3186);

        if (dispToday) {
            M5.Lcd.fillRoundRect(72, 3, 63, 15, 7, 0xdefb);

            M5.Lcd.loadFont(FONT1, SD);

            M5.Lcd.setTextColor(0x3186, 0xdefb);
            M5.Lcd.setTextDatum(4);
            M5.Lcd.drawString("TODAY", 104, 11);

            M5.Lcd.unloadFont();
        }


        M5.Lcd.loadFont(FONT2, SD);

        if(dispToday)
        {
            M5.Lcd.setTextColor(WHITE, 0x3186);
            M5.Lcd.setTextDatum(3);
            M5.Lcd.drawString(displayDateString, 141, 11);
        }else{
            M5.Lcd.setTextColor(WHITE, 0x3186);
            M5.Lcd.setTextDatum(4);
            M5.Lcd.drawString(displayDateString, 160, 11);
        }
        M5.Lcd.unloadFont();            
    }
}
