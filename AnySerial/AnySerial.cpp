/*
  AnySerial.cpp - Serial multiplexing class for Arduino
  Copyright (c) 2013 Nicolas Lopez.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include <Arduino.h>
#include "AnySerial.h"
// Constructors ////////////////////////////////////////////////////////////////

// Public Methods //////////////////////////////////////////////////////////////

void AnySerial_::begin(uint16_t baud)
{
  Serial.begin(baud);
  Serial1.begin(baud);
}

void AnySerial_::end()
{
  Serial.end();
  Serial1.end();
}

// Total
int AnySerial_::available(void)
{
  uint8_t avail = 0;
  avail += Serial.available();
  avail += Serial1.available();

  return avail;
}

int AnySerial_::peek(void)
{
  int c;
  c = Serial.peek();
  if (c != -1) return c;
  c = Serial1.peek();
  if (c != -1) return c;
  return -1;
}

int AnySerial_::read(void)
{
  int c;
  c = Serial.read();
  if (c != -1) return c;
  c = Serial1.read();
  if (c != -1) return c;
  return -1;
}

void AnySerial_::flush()
{
  Serial.flush();
  Serial1.flush();
}

// write to all serial ports
size_t AnySerial_::write(uint8_t c)
{
  Serial.write(c);
  Serial1.write(c);
// assume it worked
  return 1;
}

AnySerial_::operator bool() {
	return true;
}

// Preinstantiate Objects //////////////////////////////////////////////////////
AnySerial_ AnySerial;

