#ifndef TRIGGER_H
#define TRIGGER_H

#include <Arduino.h>

class MicroBeaut_Trigger {
private:
    bool _prevInput;
    bool _output;
    unsigned long _prevTime;
    unsigned long _currTime;
    unsigned long _usTimeDelay;
    unsigned long _usElapsedTime;

  public:
    MicroBeaut_Trigger(void);
    void setTimeDelay(uint16_t msTimeDelay);
    bool readInput(bool input = true, bool reset = false);
    bool readStatus(void);
    uint16_t getTimeDelay(void);
    uint16_t getElapsedTime(void);
};

#endif // TRIGGER_H