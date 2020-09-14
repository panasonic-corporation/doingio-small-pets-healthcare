#include "UIFaceView.h"

void UIFaceView::setup(UICellModel *_uiCellModelRef)
{
    uiCellModelRef = _uiCellModelRef;
}

void UIFaceView::setValue(float _value)
{
    value = _value;
}

void UIFaceView::draw()
{
    float goodMin = uiCellModelRef -> fgm.min;
    float goodMax = uiCellModelRef -> fgm.max;
    float sosoMin = uiCellModelRef -> fsm.min;
    float sosoMax = uiCellModelRef -> fsm.max;

    int channel = uiCellModelRef -> channel;

    enum status {
        none,
        good,
        so_so,
        bad
    };

    enum status sValue;

    if (value >= goodMin && value <= goodMax) {
        sValue = good;
    }
    else if (value >= sosoMin && value < sosoMax) {
        sValue = so_so;
    }
    else {
        sValue = bad;
    }

    // [NUMBER_OF_SENSOR][channel][facePng(x,y)]
    int paramArray[6][6][2] = {{{35, 71},{0, 0},{0, 0},{0, 0},{0, 0},{0, 0}},
                              {{64, 63},{221, 63},{0, 0},{0, 0},{0, 0},{0, 0}},
                              {{26, 53},{26, 122},{26, 192},{0, 0},{0, 0},{0, 0}},
                              {{84, 42},{84, 94},{84, 146},{84, 198},{0, 0},{0, 0}},
                              {{33, 45},{33, 114},{33, 185},{190, 45},{190, 114},{0, 0}},
                              {{33, 45},{33, 114},{33, 185},{190, 45},{190, 114},{190, 185}}};

    int faceSize = NUMBER_OF_SENSOR;
    if (faceSize > 4) {
        faceSize = 4;
    }
    int faceX = paramArray[NUMBER_OF_SENSOR - 1][channel][0];
    int faceY = paramArray[NUMBER_OF_SENSOR - 1][channel][1];

    switch (sValue) {
        case good:
        {
            String goodPngName = "/SD/faces/1f601_" + (String)faceSize + ".png";
            M5.Lcd.drawPngFile(SD, goodPngName.c_str(), faceX, faceY, WHITE);
            break;
        }

        case so_so:
        {
            String sosoPngName = "/SD/faces/1f642_" + (String)faceSize + ".png";
            M5.Lcd.drawPngFile(SD, sosoPngName.c_str(), faceX, faceY, WHITE);
            break;
        }

        case bad:
        {
            String badPngName = "/SD/faces/1f625_" + (String)faceSize + ".png";
            M5.Lcd.drawPngFile(SD, badPngName.c_str(), faceX, faceY, WHITE);
            break;
        }

        default:
        {
            break;
        }
    }
}
