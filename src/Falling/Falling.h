#ifndef FALLING_H
#define FALLING_H

#include <Arduino.h>

class MicroBeaut_Falling {
  private:
    bool _prevInput;
    bool _output;
  public:
    MicroBeaut_Falling(void);
    bool readInput(bool input);
    bool readStatus(void);
};

#endif // FALLING_H