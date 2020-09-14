#include "WifiTwitter.h"

#ifndef TWITTERCONTROLLER_H
#define TWITTERCONTROLLER_H

#include "DayDataModel.h"

class TwitterController {
  private:
    DayDataModel *nowDayDataRef;
    WifiTwitter *wifitwitterRef;
 
    bool isEnable = true;
  public:
    void setup(DayDataModel *_nowDayDataRef, char *_token);
    void tweet();
};
#endif
