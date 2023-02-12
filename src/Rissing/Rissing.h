#ifndef RISSING_H
#define RISSING_H

#include <Arduino.h>

class MicroBeaut_Rising {
  private:
    bool _prevInput;
    bool _output;
  public:
    MicroBeaut_Rising(void);
    bool readInput(bool input);
    bool readStatus(void);
};

#endif // RISSING_H