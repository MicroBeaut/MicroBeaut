#ifndef SR_H
#define SR_H

#include <Arduino.h>


class MicroBeaut_SR {
  private:
    bool _output;
  
  public:
    MicroBeaut_SR(void);
    bool readInput(bool input, bool reset = false);
    bool readStatus(void);
};

#endif // SR_H