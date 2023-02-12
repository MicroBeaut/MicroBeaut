#ifndef TIMEPULSE_H
#define TIMEPULSE_H

#include <Arduino.h>

class MicroBeaut_TimePulse {
private:
    bool _prevInput;
    bool _reset;
    bool _output;
    unsigned long _prevTime;
    unsigned long _usTimeDelay;
    unsigned long _usElapsedTime;

  public:
    MicroBeaut_TimePulse(void);
    void setTimeDelay(uint16_t msTimeDelay);
    bool readInput(bool input);
    bool readStatus(void);
    uint16_t getTimeDelay(void);
    uint16_t getElapsedTime(void);
};

#endif // TIMEPULSE_H