#ifndef TIMEROFF_H
#define TIMEROFF_H

#include <Arduino.h>

class MicroBeaut_TimerOff {
  private:
    bool _prevInput;
    bool _output;
    unsigned long _prevTime;
    unsigned long _usTimeDelay;
    unsigned long _usElapsedTime;
  
  public:
    MicroBeaut_TimerOff(void);
    void setTimeDelay(uint16_t msTimeDelay);
    bool readInput(bool input);
    bool readStatus(void);
    uint16_t getTimeDelay(void);
    uint16_t getElapsedTime(void);
};

#endif // TIMEROFF_H