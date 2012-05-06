/*
 HH10D humidity sensor reading based on code by:
 (C) Semyon Tushev, 2011.
 License: CC-BY-SA
  http://tushev.org
 
 The circuit:
 * SCL to D3
 * SDA to D2
 * FOUT to digital _pin
 * VDD to 3V3
 * GND to GND
 
 HH10D real I2C address is 81 (the datasheet contains error).
 
 The Arduino Wire code uses the internal pull-up resistors on the I2C lines,
 so no external resistors are required.
 
 * Changed to use pulseIn instead of FreqCounter because FreqCounter doesn't
   work on my Fio v3
 
 */

/* ======================================================== */
#define USE_INTERRUPTS

#include "../Wire/Wire.h"
#include "HH10D.h"

#define NUM_INTERRUPT 4
volatile long ticks[NUM_INTERRUPT];
volatile long lastRead[NUM_INTERRUPT];

void tick0(){ticks[0]++;}
void tick1(){ticks[1]++;}
void tick2(){ticks[2]++;}
void tick3(){ticks[3]++;}

typedef void (*intHandler)(void);
intHandler handlers[NUM_INTERRUPT] = {tick0,tick1,tick2,tick3};

// Need to set call setCalibration()
// or setCalibrationFromEEPROM() from setup()
HH10D::HH10D(int pin) {
  _pin = pin;
}
// Init with previously read calibration constants
// to avoid having to include Wire in the sketch
HH10D::HH10D(int pin, int sens, int offset) {
  _pin = pin;
  _sens = sens;
  _offset = offset;
  
  ticks[_pin] = 0;
  lastRead[_pin] = millis();
  attachInterrupt(_pin, handlers[_pin], RISING);
}

void HH10D::setCalibration(int sens, int offset){
  _sens = sens;
  _offset = offset;
}

void HH10D::setCalibrationFromEEPROM(){
  Wire.begin();
  _sens   = i2cRead2bytes(81, 10); //Read sensitivity from EEPROM
  _offset = i2cRead2bytes(81, 12); //Same for offset
  
  ticks[_pin] = 0;
  lastRead[_pin] = millis();
  attachInterrupt(_pin, handlers[_pin], RISING);
}

long HH10D::getFrequency() {
  long freq;
#ifndef USE_INTERRUPTS
  #define SAMPLES 4096
  for(unsigned int j=0; j<SAMPLES; j++) freq+= 500000/pulseIn(_pin, HIGH, 250000);
  return freq / SAMPLES;
#else
  freq = ticks[_pin] / ((millis() - lastRead[_pin]) / 1000);
  lastRead[_pin] = millis();
  ticks[_pin] = 0;
  return freq;
#endif
}

// getRH is slow because it has to calculate frequency, so grab it before outputting the header
float HH10D::getRH(){
  long freq = getFrequency();
  //Calculate RH
  return ((float)(_offset-freq)*_sens)/4096.0;
}

int HH10D::i2cRead2bytes(int deviceaddress, byte address){
 // SET ADDRESS
 Wire.beginTransmission(deviceaddress);
 Wire.write(address); // address for sensitivity
 Wire.endTransmission();

 // REQUEST RETURN VALUE
 Wire.requestFrom(deviceaddress, 2);
 // COLLECT RETURN VALUE
 int rv = 0;
 for (int c = 0; c < 2; c++ )
 if (Wire.available()) rv = (rv << 8) | Wire.read();
 return rv;
}