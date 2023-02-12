#ifndef TOGGLE_H
#define TOGGLE_H

#include <Arduino.h>


class MicroBeaut_Toggle {
  private:
    bool _prevInput;
    bool _output;
  
  public:
    MicroBeaut_Toggle(void);
    bool readInput(bool input, bool reset = false);
    bool readStatus(void);
};

#endif // TOGGLE_H