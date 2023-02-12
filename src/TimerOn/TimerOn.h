#ifndef TIMERON_H
#define TIMERON_H

#include <Arduino.h>

class MicroBeaut_TimerOn {
private:
    bool _prevInput;
    bool _output;
    unsigned long _prevTime;
    unsigned long _usTimeDelay;
    unsigned long _usElapsedTime;

  public:
    MicroBeaut_TimerOn(void);
    void setTimeDelay(uint16_t msTimeDelay = 1000);
    bool readInput(bool input);
    bool readStatus(void);
    uint16_t getTimeDelay(void);
    uint16_t getElapsedTime(void);
};

#endif // TIMERON_H