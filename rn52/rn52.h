
#ifndef RH52LIB
#define RH52LIB
#include <Arduino.h>

class RN52 {
  public:
  RN52(int cmdpin, Stream& uartin);
  
  void
    begin(void),
    play(void),
    nextTrack(void),
    prevTrack(void),
    volUp(void),
    volDown(void),
    answer(void),
    hangup(void);
    void sendCommand(String cmd);
    
    boolean isTalking(void);
    boolean isPlaying(void);
  
  private:
    Stream& uart;
    int cmdpin;
    uint16_t status();
    void startCommandMode();
    void endCommandMode();
};

#endif
