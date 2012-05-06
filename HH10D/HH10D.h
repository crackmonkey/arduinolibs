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
		void setCalibration(int sens, int offset);
		void setCalibrationFromEEPROM();
		int _sens;
		int _offset;
	private:
		int i2cRead2bytes(int deviceaddress, byte address);
		long getFrequency();
		int _pin;
};

#endif