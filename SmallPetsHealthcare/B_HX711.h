#include "Arduino.h"

#ifndef __B_HX711_H
#define __B_HX711_H

class B_HX711 {
  private:
    void Init();
    void Reset();
    long Read();
    long Averaging(char NUM);
    

    int DOUT_PIN;
    int SLK_PIN;
    float OUT_VOL = 0.001f;
    float LOAD =  1000.0f;
    float CALIB = 1.18;//1kg

    
  public:
    void Setup(int _DOUT_PIN, int _SLK_PIN, float _OUT_VOL, float _LOAD, float _CALIB);
    float getVal();
    float getGram(char NUM);
    float offset;
};
#endif
