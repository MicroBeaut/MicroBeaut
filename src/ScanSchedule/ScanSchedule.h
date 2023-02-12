#ifndef SCANSCHEDULE_H
#define SCANSCHEDULE_H

#include <Arduino.h>

class MicroBeaut_ScanSchedule {
  private:
    typedef void (*MicroBeaut_CallBackFunction)(void);
    MicroBeaut_CallBackFunction _callBackFunction;
    bool _prevEnable;
    bool _output;
    unsigned long _numberOfScan;
    unsigned long _currNumberOfScan;
    unsigned long _actual;
    unsigned long _prevTime;
    unsigned long _currTime;
    unsigned long _usElapsedTime;

  public:
    MicroBeaut_ScanSchedule(void);
    void setScanSchedule(unsigned long numberOfScan, MicroBeaut_CallBackFunction functionName = nullptr);
    bool readInput(bool enable = true);
    uint16_t getElapsedTime(void);
    bool readStatus(void);
};

#endif // SCANSCHEDULE_H