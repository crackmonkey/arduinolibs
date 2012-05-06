/* 
 Testing / Example code for HH10D Relative Humidity sensor
 Arduino library. 
 
 I requires the Wire library if you don't hard-code the
 calibration constants
 */

#include <Wire.h>
#include <HH10D.h>

// HH10D fout pin is connected to digital 4
// sensitivity = 360, offset = 7617
HH10D rh(4);

void setup(){
  Serial.begin(9600);
  rh.setCalibrationFromEEPROM();
}

// Dump out the RH reading as well as the values read from the EEPROM
void loop(){
  float humdity;
  int before = millis();
  humdity = rh.getRH();
  int after = millis();
  Serial.print("time:");
  Serial.print(after-before);
  Serial.println("ms");
  Serial.print("RH:");
  Serial.println(humdity);
  Serial.print("sens:");
  Serial.println(rh._sens);
  Serial.print("offset:");
  Serial.println(rh._offset);
}

