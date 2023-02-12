#ifndef MicroBeaut_h
#define MicroBeaut_h

#include "Arduino.h"

/*
  -- ======================================================================================
  -- Library: MicorBeaut
  -- Version: V1.1.2
  -- Date:    13-Mar-2022
  -- Author:  Montree Hamarn, Natvalun Tavepontakul
  -- Email:   montree.hamarn@gmail.com, natvalun.tavepontakul@hotmail.com
  -- GitHub:  https://github.com/MicroBeaut
  -- YouTube: What Did You Learn Today
  --          https://www.youtube.com/playlist?list=PLFf3xtcn9d47akU0G3bf2BXiMebCzrvMm
  -- ======================================================================================
*/


class MicroBeaut_SR {
  public:
    MicroBeaut_SR(void);
    bool SR(bool setInput, bool resetInput = false);
    bool Output(void);

  private:
    bool _output;
};


class MicroBeaut_RS
{
  public:
    MicroBeaut_RS(void);
    bool RS(bool setInput, bool resetInput = false);
    bool Output(void);

  private:
    bool _output;
};


class MicroBeaut_Toggle
{
  public:
    MicroBeaut_Toggle(void);
    bool Toggle(bool toggleInput, bool resetInput = false);
    bool Output(void);

  private:
    bool _prevInput;
    bool _output;
};


class MicroBeaut_Rising
{
  public:
    MicroBeaut_Rising(void);
    bool Rising(bool risingInput);
    bool Output(void);

  private:
    bool _prevInput;
    bool _output;
};


class MicroBeaut_Falling
{
  public:
    MicroBeaut_Falling(void);
    bool Falling(bool fallingInput);
    bool Output(void);

  private:
    bool _prevInput;
    bool _output;
};


class MicroBeaut_Debounce
{
  public:
    MicroBeaut_Debounce(void);
    void SetTimeDebounce(float timeDebounce = 0.01);
    bool Debounce(bool bounceInput);
    bool Output(void);
    float GetTimeDebounce(void);
    float GetElapsedTime(void);

  private:
    bool _input;
    bool _prevInput;
    bool _output;
    unsigned long _prveTime;
    unsigned long _timeDebounce = 10000UL;
    unsigned long _elapsedTime;
};


class MicroBeaut_TimerOn
{
  public:
    MicroBeaut_TimerOn(void);
    void SetTimeDelay(float timeDelay);
    bool TimerOn(bool timerOnInput);
    bool Output(void);
    float GetTimeDelay(void);
    float GetElapsedTime(void);

  private:
    bool _prevInput;
    bool _output;
    unsigned long _prveTime;
    unsigned long _timeDelay;
    unsigned long _elapsedTime;
};


class MicroBeaut_TimerOff
{
  public:
    MicroBeaut_TimerOff(void);
    void SetTimeDelay(float timeDelay);
    bool TimerOff(bool timerOffInput);
    bool Output(void);
    float GetTimeDelay(void);
    float GetElapsedTime(void);


  private:
    bool _prevInput;
    bool _output;
    unsigned long _prveTime;
    unsigned long _timeDelay;
    unsigned long _elapsedTime;
};


class MicroBeaut_Blink
{
  public:
    MicroBeaut_Blink(void);
    void SetTimeDelay(float timeDelayOff, float timeDelayOn);
    bool Blink(bool enableInput = true);
    bool Output(void);
    float GetTimeDelayOn(void);
    float GetTimeDelayOff(void);
    float GetElapsedTime(void);

  private:
    bool _prevInput;
    bool _output;
    unsigned long _prevTime;
    unsigned long _currTime;
    unsigned long _timeDelayOn;
    unsigned long _timeDelayOff;
    unsigned long _elapsedTime;
};


class MicroBeaut_TimePulse
{
  public:
    MicroBeaut_TimePulse(void);
    void SetTimeDelay(float timeDelay);
    bool TimePulse(bool pulseInput);
    bool Output(void);
    float GetTimeDelay(void);
    float GetElapsedTime(void);

  private:
    bool _prevInput;
    bool _reset;
    bool _output;
    unsigned long _prveTime;
    unsigned long _timeDelay;
    unsigned long _elapsedTime;
};


class MicroBeaut_Trigger
{
  public:
    MicroBeaut_Trigger(void);
    void SetTimeDelay(float timeDelay);
    bool Trigger(bool enableInput = true, bool resetInput = false);
    bool Output(void);
    float GetTimeDelay(void);
    float GetElapsedTime(void);

  private:
    bool _prevInput;
    bool _output;
    unsigned long _prveTime;
    unsigned long _currTime;
    unsigned long _timeDelay;
    unsigned long _elapsedTime;
};


typedef void (*MicroBeaut_CallBackFunction)(void);
class MicroBeaut_TimeSchedule {

  public:
    MicroBeaut_TimeSchedule(void);
    void Config(float timeSchedule, MicroBeaut_CallBackFunction functionName);
    bool Run(bool enableInput = true);
    float Actual(void);
    bool Output(void);

  private:
    MicroBeaut_CallBackFunction _callBackFunction;
    bool _prevEnable;
    bool _output;
    unsigned long _actual;
    unsigned long _timeSchedule;
    unsigned long _prveTime;
    unsigned long _currTime;
    unsigned long _elapsedTime;
};


class MicroBeaut_ScanSchedule {
  public:
    MicroBeaut_ScanSchedule(void);
    void Config(unsigned long numberOfScan, MicroBeaut_CallBackFunction functionName);
    bool Run(bool enableInput = true);
    float Actual(void);
    bool Output(void);

  private:
    MicroBeaut_CallBackFunction _callBackFunction;
    bool _prevEnable;
    bool _output;
    unsigned long _numberOfScan;
    unsigned long _currNumberOfScan;
    unsigned long _actual;
    unsigned long _prveTime;
    unsigned long _currTime;
    unsigned long _elapsedTime;
};

#endif