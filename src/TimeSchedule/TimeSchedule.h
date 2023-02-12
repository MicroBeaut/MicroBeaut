#ifndef TIMESCHEDULE_H
#define TIMESCHEDULE_H

#include <Arduino.h>


class MicroBeaut_TimeSchedule {
  private:
    typedef void (*MicroBeaut_CallBackFunction)(void);
    MicroBeaut_CallBackFunction _callBackFunction;
    bool _prevEnable;
    bool _output;
    unsigned long _actual;
    unsigned long _timeSchedule;
    unsigned long _prevTime;
    unsigned long _currTime;
    unsigned long _usElapsedTime;
  public:
    MicroBeaut_TimeSchedule(void);
    void setTimeSchedule(uint16_t msTimeSchedule, MicroBeaut_CallBackFunction functionName = nullptr);
    bool readInput(bool enable = true);
    uint16_t getElapsedTime(void);
    bool readStatus(void);
};

#endif // TIMESCHEDULE_H