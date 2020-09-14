#include "WeightController.h"


void WeightController::setup(DayDataModel *_nowDayDataRef, int _channel, int _DOUT_PIN, int _SLK_PIN, float _threshold, float _OUTVOL, float _LOAD , float _CALIB) {
  nowDayDataRef = _nowDayDataRef;
  channel = _channel;
  threshold = _threshold;
  // void Setup(int _DOUT_PIN, int _SLK_PIN, float _OUT_VOL, float _LOAD, float _CALIB);
 
  //初期値
  for(int i = 0; i < WEIGHT_FIL; i++)
  { 
    weightArray[i] == nowDayDataRef->sensorsValue[channel];
  }
 
  if(channel > NOCH)
  {
    bhx711.Setup(_DOUT_PIN, _SLK_PIN, _OUTVOL, _LOAD, _CALIB);
    reset();
  }
}

void WeightController::update() {
  if(channel > NOCH)
  {
    float avg = 0;
    float getData = bhx711.getVal();

    if (getData >= threshold) { //閾値より高い時だけ計測

      weightArray[weightArrayIndex++] = getData;
      if(weightArrayIndex >= WEIGHT_FIL) weightArrayIndex = 0;
    
      float sum = 0;
      int cnt = 0;
      for(int i = 0; i < WEIGHT_FIL; i++)
      {
        if(weightArray[i] >= threshold )
        {
          sum += weightArray[i];
          cnt++;
        }
      }
      avg = sum/(float)cnt;
      if(cnt > 0) nowDayDataRef->sensorsValue[channel] = avg;
    }
    
    

    //debug output
    Serial.print("Weight weight: ");
    Serial.print(getData);
    Serial.print (", avg: ");
    Serial.println (avg);
  }
}

void WeightController::reset() {
  for(int i = 0; i < WEIGHT_FIL; i++)
  { 
    weightArray[i] == nowDayDataRef->sensorsValue[channel];
  }

  if(channel > NOCH)
    bhx711.offset = bhx711.getGram(30);
}
