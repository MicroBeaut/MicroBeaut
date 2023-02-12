
#ifndef BLINK_H
#define BLINK_H

#include <Arduino.h>


class MicroBeaut_Blink {
  private:
    bool _prevInput;
    bool _output;
    unsigned long _prevTime;
    unsigned long _currTime;
    unsigned long _timeDelayOn;
    unsigned long _timeDelayOff;
    unsigned long _usElapsedTime;

  public:
    MicroBeaut_Blink(void);
    void setTimeDelay(uint16_t timeDelayOff, uint16_t timeDelayOn);
    bool readInput(bool enable = true);
    bool readStatus(void);
    uint16_t getTimeDelayOn(void);
    uint16_t getTimeDelayOff(void);
    uint16_t getElapsedTime(void);

  
};

#endif // BLINK_H