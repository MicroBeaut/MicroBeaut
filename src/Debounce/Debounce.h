#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#include <Arduino.h>

class MicroBeaut_Debounce {
private:
    bool _input;
    bool _prevInput;
    bool _output;
    unsigned long _prevTime;
    unsigned long _usTimeDebounce = 10000UL;
    unsigned long _usElapsedTime;

  public:
    MicroBeaut_Debounce(void);
    void setTimeDebounce(uint16_t msTimeDebounce = 10);
    bool readInput(bool input);
    bool readStatus(void);
    uint16_t getTimeDebounce(void);
    uint16_t getElapsedTime(void);
};

#endif // DEBOUNCE_H