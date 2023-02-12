#ifndef RS_H
#define RS_H

#include <Arduino.h>

class MicroBeaut_RS {
  private:
    bool _output;

  public:
    MicroBeaut_RS(void);
    bool readInput(bool input, bool reset = false);
    bool readStatus(void);
};

#endif // RS_H