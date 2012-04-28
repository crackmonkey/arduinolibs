/*
class for HH10D humidity sensor
Based on Semyon Tushev's sweet example code
*/

#ifndef HH10D_h
#define HH10D_h

#include "Arduino.h"

class HH10D {
	public:
		HH10D(int pin);
		HH10D(int pin, int sens, int offset);
		float getRH();
		int _sens;
		int _offset;
		private:
		int i2cRead2bytes(uint8_t deviceaddress, uint8_t address);
		long getFrequency();
		int _pin;

};

#endif