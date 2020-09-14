#include "B_HX711.h"

void B_HX711::Setup(int _DOUT_PIN, int _SLK_PIN, float _OUT_VOL, float _LOAD, float _CALIB) {
  DOUT_PIN = _DOUT_PIN;
  SLK_PIN = _SLK_PIN;
  OUT_VOL = _OUT_VOL;
  LOAD = _LOAD;
  CALIB = _CALIB;
  
  Init();
  Reset();
  offset = getGram(30); 
}


float B_HX711::getVal() {
  float data;
  char S1[20];
  char s[20];
  data = getGram(5);
  data = data - offset;

  return data * CALIB;
}


void B_HX711::Init(){
  pinMode(SLK_PIN, OUTPUT);
  pinMode(DOUT_PIN, INPUT);
}


void  B_HX711::Reset() {
  digitalWrite(SLK_PIN, 1);
  delayMicroseconds(100);
  digitalWrite(SLK_PIN, 0);
  delayMicroseconds(100);
}


long B_HX711::Read() {
  long data = 0;
  while (digitalRead(DOUT_PIN) != 0);
  delayMicroseconds(10);
  for (int i = 0; i < 24; i++)
  {
    digitalWrite(SLK_PIN, 1);
    delayMicroseconds(5);
    digitalWrite(SLK_PIN, 0);
    delayMicroseconds(5);
    data = (data << 1) | (digitalRead(DOUT_PIN));
  }
  digitalWrite(SLK_PIN, 1);
  delayMicroseconds(10);
  digitalWrite(SLK_PIN, 0);
  delayMicroseconds(10);
  return data ^ 0x800000;
}


long B_HX711::Averaging(char NUM) {
  long SUM = 0;
  for (int i = 0; i < NUM; i++) SUM += Read();
  return SUM / NUM;
}


float B_HX711::getGram(char NUM) {
#define HX711_R1  20000.0f
#define HX711_R2  8200.0f
#define HX711_VBG 1.25f
#define HX711_AVDD      4.2987f
#define HX711_ADC1bit   HX711_AVDD/16777216
#define HX711_PGA 128
#define HX711_SCALE     (OUT_VOL * HX711_AVDD / LOAD *HX711_PGA)

  float data;

  data = Averaging(NUM) * HX711_ADC1bit;
  data =  data / HX711_SCALE;

  return data;
}
