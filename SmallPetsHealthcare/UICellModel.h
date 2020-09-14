#ifndef UICELLMODEL_H
#define UICELLMODEL_H

#include "DayDataModel.h"
#include "DisplayDataModel.h"
#include <M5Stack.h>

class UICellModel
{
public:
    String title;
    int channel;
    bool valueIsInt;
    DisplayDataModel *displayDataRef;
    DayDataModel *nowDayDataRef;

    typedef struct faceGoodThr {
        float min;
        float max;
    }FG_MINMAX;

    typedef struct faceSosoThr {
        float min;
        float max;
    }FS_MINMAX;

    typedef struct graphThr {
        float min;
        float max;
    }GRAPH_MINMAX;

    FG_MINMAX fgm;
    FS_MINMAX fsm;
    GRAPH_MINMAX gm;
};

#endif
