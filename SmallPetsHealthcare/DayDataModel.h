#ifndef DAYDATAMODEL_H
#define DAYDATAMODEL_H

#include <time.h>

class DayDataModel
{
public:
  struct tm nowtimeInfo;
  float sensorsValue[6];
  bool isCheck;
};
#endif
