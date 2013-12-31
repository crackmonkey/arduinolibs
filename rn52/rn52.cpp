
#include "rn52.h"
#include <Stream.h>

RN52::RN52(int cmdpinin, Stream& uartin) 
:uart(uartin),
 cmdpin(cmdpinin)
{
}

void RN52::begin() {
  // make sure we're in normal data pipe mode, not command mode
  pinMode(cmdpin, OUTPUT);
  digitalWrite(cmdpin, HIGH);
}

void RN52::startCommandMode() {
#ifdef DEBUG
  Serial.println("RN52:Bringing "+String(cmdpin)+" low");
#endif
  digitalWrite(cmdpin, LOW);

  uart.find("CMD\r\n");
#ifdef DEBUG
  Serial.println("Found CMD");
#endif
  // wait for CMD
}

void RN52::endCommandMode() {
#ifdef DEBUG
  Serial.println("RN52:Bringing "+String(cmdpin)+" high");
#endif
  digitalWrite(cmdpin, HIGH);
#ifdef DEBUG
  Serial.println("RN52:Waiting for END");
#endif
  uart.find("END\r\n");
#ifdef DEBUG
  Serial.println("RN52:Got END");
#endif
}

void RN52::sendCommand(String cmd) {
  startCommandMode();
  uart.println(cmd);
#ifdef DEBUG
  Serial.println("RH52>"+cmd);
#endif
  endCommandMode();
}

// byte 0
// BIT_0 iAP
// BIT_1 SPP
// BIT_2 A2DP
// BIT_3 HFP/HSP
const uint16_t STATUS_iAP = bit(0);
const uint16_t STATUS_SPP = bit(1);
const uint16_t STATUS_A2DP = bit(2);

// byte 1, don't care for now
// 0-3 con status
// 4 HFP audio level
// 5 HFP mic level

uint16_t RN52::status() {
  char buf[32];
  uint16_t stat;
  byte bytes;

  startCommandMode();

  // wait for CMD
  uart.println("Q");

  // read byte
  bytes = uart.readBytesUntil('\n', buf, 31);
  buf[bytes] = 0; // NUL terminate
  stat = strtol(buf, NULL, 16);  
  endCommandMode();

  return stat;
}

void RN52::play() {
  sendCommand("AP");
}

void RN52::volUp() {
  sendCommand("AV+");
}

void RN52::volDown() {
  sendCommand("AV-");
}

void RN52::nextTrack() {
  sendCommand("AT+");
}

void RN52::prevTrack() {
  sendCommand("AT-");
}

void RN52::answer() {
  sendCommand("C");
}

void RN52::hangup() {
  sendCommand("E");
}



