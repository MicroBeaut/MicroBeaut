#ifndef MicroBeaut_h
#define MicroBeaut_h

#include "Arduino.h"



class MicroBeaut_SR {
  public:
    MicroBeaut_SR(void);
    bool SR(bool Set, bool Reset);

  private:
    bool _set;
    bool _reset;
    bool _output;
    bool _SR(void);
};


class MicroBeaut_RS
{
  public:
    MicroBeaut_RS(void);
    bool RS(bool Set, bool Reset);

  private:
    bool _set;
    bool _reset;
    bool _output;
    bool _RS(void);
};


class MicroBeaut_Toggle
{
  public:
    MicroBeaut_Toggle(void);
    bool Toggle(bool Input);
    bool Toggle(bool Input, bool Reset);

  private:
    bool _input;
    bool _prevInput;
    bool _reset;
    bool _output;
    bool _Toggle(void);
};


class MicroBeaut_Rising
{
  public:
    MicroBeaut_Rising(void);
    bool Rising(bool Input);

  private:
    bool _input;
    bool _prevInput;
    bool _output;
    bool _Rising(void);
};


class MicroBeaut_Falling
{
  public:
    MicroBeaut_Falling(void);
    bool Falling(bool Input);


  private:
    bool _input;
    bool _prevInput;
    bool _output;
    bool _Falling(void);
};


class MicroBeaut_Debounce
{
  public:
    MicroBeaut_Debounce(void);
    void SetTimeDelay(float TimeDelay);
    bool Debounce(bool Input);
    bool Debounce(bool Input, float TimeDelay);
    float GetTimeDelay(void);
    float GetElapsedTime(void);

  private:
    bool _input;
    bool _prevInput;
    bool _output;
    unsigned long _prveTime;
    unsigned long _timeDelay;
    unsigned long _elapsedTime;
    bool _Debounce(void);
};


class MicroBeaut_TimerOn
{
  public:
    MicroBeaut_TimerOn(void);
    void SetTimeDelay(float TimeDelay);
    bool TimerOn(bool Input);
    bool TimerOn(bool Input, float TimeDelay);
    float GetTimeDelay(void);
    float GetElapsedTime(void);


  private:
    bool _input;
    bool _prevInput;
    bool _output;
    unsigned long _prveTime;
    unsigned long _timeDelay;
    unsigned long _elapsedTime;
    bool _TimerOn(void);
};


class MicroBeaut_TimerOff
{
  public:
    MicroBeaut_TimerOff(void);
    void SetTimeDelay(float TimeDelay);
    bool TimerOff(bool Input);
    bool TimerOff(bool Input, float TimeDelay);
    float GetTimeDelay(void);
    float GetElapsedTime(void);


  private:
    bool _input;
    bool _prevInput;
    bool _output;
    unsigned long _prveTime;
    unsigned long _timeDelay;
    unsigned long _elapsedTime;
    bool _TimerOff(void);
};


class MicroBeaut_Blink
{
  public:
    MicroBeaut_Blink(void);
    void SetTimeDelay(float TimeDelay);
    void SetTimeDelay(float TimeDelayOff, float TimeDelayOn);
    bool Blink(bool Input);
    bool Blink(bool Input, float TimeDelay);
    bool Blink(bool, float TimeDelayOff, float TimeDelayOn);
    float GetTimeDelayOn(void);
    float GetTimeDelayOff(void);
    float GetElapsedTime(void);

  private:
    bool _input;
    bool _prevInput;
    bool _output;
    unsigned long _prevTime;
    unsigned long _currTime;
    unsigned long _timeDelayOn;
    unsigned long _timeDelayOff;
    unsigned long _elapsedTime;
    bool _Blink(void);
};


class MicroBeaut_TimePulse
{
  public:
    MicroBeaut_TimePulse(void);
    void SetTimeDelay(float TimeDelay);
    bool TimePulse(bool Input);
    bool TimePulse(bool Input, float TimeDelay);
    float GetTimeDelay(void);
    float GetElapsedTime(void);

  private:
    bool _input;
    bool _prevInput;
    bool _reset;
    bool _output;
    unsigned long _prveTime;
    unsigned long _timeDelay;
    unsigned long _elapsedTime;
    bool _TimePulse(void);
};


class MicroBeaut_Trigger
{
  public:
    MicroBeaut_Trigger(void);
    void SetTimeDelay(float TimeDelay);
    bool Trigger(bool Input);
    bool Trigger(bool Input, bool Reset);
    bool Trigger(bool Input, bool Reset, float TimeDelay);
    float GetTimeDelay(void);
    float GetElapsedTime(void);

  private:
    bool _input;
    bool _reset;
    bool _prevInput;
    bool _output;
    unsigned long _prveTime;
    unsigned long _currTime;
    unsigned long _timeDelay;
    unsigned long _elapsedTime;

    bool _Trigger(void);
};
#endif