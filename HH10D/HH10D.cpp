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
 + pullup resistors for i2c(4k7, 10k) (http://www.nxp.com/news/backgrounders/bg_esc9727/)
 
 HH10D real I2C address is 81 (the datasheet contains error).
 
 */

/* ======================================================== */

#include "../I2C/I2C.h"
#include "HH10D.h"

//--------------------------
// Read the calibration data over I2C
HH10D::HH10D(int pin) {
  _pin = pin;
  
  I2c.begin();
  _sens   = i2cRead2bytes(81, 10); //Read sensitivity from EEPROM
  _offset = i2cRead2bytes(81, 12); //Same for offset
  I2c.end();
}
// Read the calibration data over I2C
HH10D::HH10D(int pin, int sens, int offset) {
  _pin = pin;
  _sens = sens;
  _offset = offset;
}

long HH10D::getFrequency() {
  #define SAMPLES 4096
  long freq = 0;
  for(unsigned int j=0; j<SAMPLES; j++) freq+= 500000/pulseIn(_pin, HIGH, 250000);
  return freq / SAMPLES;
}

// getRH is slow because it has to calculate frequency, so grab it before outputting the header
float HH10D::getRH(){
 long freq = getFrequency();
 
 //Calculate RH
 return ((float)(_offset-freq)*_sens)/4096.0;
}

int HH10D::i2cRead2bytes(uint8_t deviceaddress, uint8_t address){
  I2c.read(deviceaddress, address, (uint8_t)2);
  return (I2c.receive() << 8) | I2c.receive();
}