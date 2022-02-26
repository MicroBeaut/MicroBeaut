#include "MicroBeaut.h"
#include "Arduino.h"


/*
  -- ========================================================
  -- Library: MicorBeaut
  -- Version: V1.1.1
  -- Date:    26-Feb-2022
  -- Author:  Montree Hamarn
  -- Email:  montree.hamarn@gmail.com
  -- GitHub:  https://github.com/MicroBeaut
  -- YouTube: What Did You Learn Today
  --          https://www.youtube.com/playlist?list=PLFf3xtcn9d47akU0G3bf2BXiMebCzrvMm
  -- ========================================================
*/



/*
  ===========================================================================
  Function:  SR
  Purpose:  Set Dominant

  Function SR is a set dominant latch. The set input sets the
  latch. The reset input resets the latch if the set input is FALSE.

  ===========================================================================
*/
MicroBeaut_SR::MicroBeaut_SR(void) {
  _set = false;
  _reset = false;
}

bool MicroBeaut_SR::SR(bool Set, bool Reset) {
  _set = Set;
  _reset = Reset;
  return this->_SR();
}

bool MicroBeaut_SR::_SR(void) {
  _output = _set | (!_reset & _output);
  return _output;
}

bool MicroBeaut_SR::Output(void) {
  return _output;
}


/*
  ===========================================================================
  Function: RS
  Purpose:  Reset Dominant

  Function RS is a reset dominant latch. The reset input resets the
  latch. The set input sets the latch if the reset input is FALSE.

  ===========================================================================
*/
MicroBeaut_RS::MicroBeaut_RS(void) {
  _set = false;
  _reset = false;
}

bool MicroBeaut_RS::RS(bool Set, bool Reset) {
  _set = Set;
  _reset = Reset;
  return this->_RS();
}

bool MicroBeaut_RS::_RS(void) {
  _output = (_set | _output) & !_reset;
  return _output;
}

bool MicroBeaut_RS::Output(void) {
  return _output;
}



/*
  ===========================================================================
  Function:  Toggle
  Purpose:   Toggle.

  The rising edge of input "Input" toggles Output.
  Input "Reset" resets Output (to FALSE).
  ===========================================================================
*/
MicroBeaut_Toggle::MicroBeaut_Toggle(void) {
  _input = false;
  _prevInput = false;
  _reset = false;
}

bool MicroBeaut_Toggle::Toggle(bool Input) {
  _input = Input;
  return this->_Toggle();
}

bool MicroBeaut_Toggle::Toggle(bool Input, bool Reset) {
  _input = Input;
  _reset = Reset;
  return this->_Toggle();
}

bool MicroBeaut_Toggle::_Toggle(void) {
  if (_reset) {
    _output = false;
  }
  else {
    _output ^= _input & !_prevInput;
  }
  _prevInput = _input;
  return _output;
}

bool MicroBeaut_Toggle::Output(void) {
  return _output;
}



/*
  ===========================================================================
  Function: Rising
  Purpose:  Rising Edge Detector

  Set Output on the rising edge of Input.
  ===========================================================================
*/
MicroBeaut_Rising::MicroBeaut_Rising(void)
{
  _input = false;
  _prevInput = false;
}

bool MicroBeaut_Rising::Rising(bool Input)
{
  _input = Input;
  return this->_Rising();
}

bool MicroBeaut_Rising::_Rising(void)
{
  _output = _input & !_prevInput;
  _prevInput = _input;
  return _output;
}

bool MicroBeaut_Rising::Output(void) {
  return _output;
}



/*
  ===========================================================================
  Function:    Falling
  Purpose:     falling Edge Detector

  Set Output on the falling edge of Input.
  ===========================================================================
*/
MicroBeaut_Falling::MicroBeaut_Falling(void)
{
  _input = false;
  _prevInput = false;
}

bool MicroBeaut_Falling::Falling(bool Input)
{
  _input = Input;
  return this->_Falling();
}

bool MicroBeaut_Falling::_Falling(void)
{
  _output = !_input & _prevInput;
  _prevInput = _input;
  return _output;
}

bool MicroBeaut_Falling::Output(void) {
  return _output;
}



/*
  ===========================================================================
  Function:  Debounce
  Purpose:   Debounce.

  The rising edge of input "Input" starts a timer of duration "TimeDelay".
  When the elapsed time is greater than or equal to "TimeDelay",
  the timer stops and output changes from FALSE to TRUE.

  The falling edge of input "Input" starts a timer of duration "TimeDelay".
  When the elapsed time is greater than or equal to "TimeDelay",
  the timer stops and output changes from TRUE to FALSE.
  ===========================================================================
*/
MicroBeaut_Debounce::MicroBeaut_Debounce(void) {
  _input = false;
  _prevInput = false;
  _timeDelay = 10000UL;
}

void MicroBeaut_Debounce::SetTimeDelay(float TimeDelay) {
  _timeDelay = TimeDelay * 1000000.0;
}

bool MicroBeaut_Debounce::Debounce(bool Input) {
  _input = Input;
  return this->_Debounce();
}

bool MicroBeaut_Debounce::Debounce(bool Input, float TimeDelay) {
  _input = Input;
  this->SetTimeDelay(TimeDelay);
  return this->_Debounce();
}

float MicroBeaut_Debounce::GetTimeDelay(void) {
  return ((float)_timeDelay * 0.000001);
}

float MicroBeaut_Debounce::GetElapsedTime(void) {
  return ((float)_elapsedTime * 0.000001);
}

bool MicroBeaut_Debounce::_Debounce(void) {
  if (_input != _prevInput) {
    _prveTime = micros();
  }
  if (_input != _output) {
    _elapsedTime = micros() - _prveTime;
    if (_elapsedTime >= _timeDelay) {
      _output = _input;
      _elapsedTime = _timeDelay;
    }
  }
  else {
    _elapsedTime = 0UL;
  }
  _prevInput = _input;
  return _output;
}

bool MicroBeaut_Debounce::Output(void) {
  return _output;
}



/*
  ===========================================================================
  Function: TimerOn
  Purpose:  Timer On

  The rising edge of input "Input" starts a timer of duration "TimeDelay".
  When the elapsed time is greater than or equal to "TimeDelay",
  the timer stops and output changes from FALSE to TRUE.
  The next falling edge of input "Input" initializes the timer
  ===========================================================================
*/
MicroBeaut_TimerOn::MicroBeaut_TimerOn(void) {
  _input = false;
  _prevInput = false;
}

void MicroBeaut_TimerOn::SetTimeDelay(float TimeDelay) {
  _timeDelay = TimeDelay * 1000000.0;
}

bool MicroBeaut_TimerOn::TimerOn(bool Input) {
  _input = Input;
  return this->_TimerOn();
}

bool MicroBeaut_TimerOn::TimerOn(bool Input, float TimeDelay) {
  _input = Input;
  this->SetTimeDelay(TimeDelay);
  return this->_TimerOn();
}

float MicroBeaut_TimerOn::GetTimeDelay(void) {
  return ((float)_timeDelay * 0.000001);
}

float MicroBeaut_TimerOn::GetElapsedTime(void) {
  return ((float)_elapsedTime * 0.000001);
}

bool MicroBeaut_TimerOn::_TimerOn(void) {
  if (_input) {
    if (!_prevInput) {
      _prveTime = micros();
    }
    _elapsedTime = micros() - _prveTime;
    if (_elapsedTime >= _timeDelay) {
      _output = true;
      _elapsedTime = _timeDelay;
    }
  }
  else {
    _output = false;
    _elapsedTime = 0UL;
  }
  _prevInput = _input;
  return _output;
}

bool MicroBeaut_TimerOn::Output(void) {
  return _output;
}



/*
  ===========================================================================
  Function: TimerOff
  Purpose:  Timer Off.

  The falling edge of input "Input" starts a timer of duration "TimeDelay".
  When the elapsed time is greater than or equal to "TimeDelay",
  the timer stops and output changes from TRUE to FALSE.
  If input "Input" is TRUE, then TimerOff sets output to TRUE and the elapsed time to zero.
  ===========================================================================
*/
MicroBeaut_TimerOff::MicroBeaut_TimerOff(void) {
  _input = false;
  _prevInput = false;
  _output = false;
}

void MicroBeaut_TimerOff::SetTimeDelay(float TimeDelay) {
  _timeDelay = TimeDelay * 1000000.0;
}

bool MicroBeaut_TimerOff::TimerOff(bool Input) {
  _input = Input;
  return this->_TimerOff();
}

bool MicroBeaut_TimerOff::TimerOff(bool Input, float TimeDelay) {
  _input = Input;
  this->SetTimeDelay(TimeDelay);
  return this->_TimerOff();
}

float MicroBeaut_TimerOff::GetTimeDelay(void) {
  return ((float)_timeDelay * 0.000001);
}

float MicroBeaut_TimerOff::GetElapsedTime(void) {
  return ((float)_elapsedTime * 0.000001);
}

bool MicroBeaut_TimerOff::_TimerOff(void) {
  if (_input) {
    _output = true;
    _elapsedTime = 0UL;
  }
  else {
    if (_prevInput) {
      _prveTime = micros();
    }
    _elapsedTime =  micros() - _prveTime;
    if (_elapsedTime >= _timeDelay) {
      _output = false;
      _elapsedTime = _timeDelay;
    }
  }
  _prevInput = _input;
  return _output;
}

bool MicroBeaut_TimerOff::Output(void) {
  return _output;
}


/*
  ===========================================================================
  Function: Blink
  Purpose:  Blink.

  Input "Input" enables blinking. Input "TimeDelayOn" gives the minimum time that the output is TRUE.
  Input "TimeDelayrOff" gives the minimum time that the output is FALSE.
  The output does not change if "Input" is FALSE.
  ===========================================================================
*/
MicroBeaut_Blink::MicroBeaut_Blink(void) {
  _input = false;
  _prevInput = false;
  _output = false;
}

void MicroBeaut_Blink::SetTimeDelay(float TimeDelay) {
  this->SetTimeDelay(TimeDelay, TimeDelay);
}

void MicroBeaut_Blink::SetTimeDelay(float TimeDelayOff, float TimeDelayOn) {
  _timeDelayOff = TimeDelayOff * 1000000.0;
  _timeDelayOn = TimeDelayOn * 1000000.0;
}

bool MicroBeaut_Blink::Blink(bool Input) {
  _input = Input;
  return this->_Blink();
}

bool MicroBeaut_Blink::Blink(bool Input, float TimeDelay) {
  _input = Input;
  this->SetTimeDelay(TimeDelay, TimeDelay);
  return this->_Blink();
}

bool MicroBeaut_Blink::Blink(bool Input, float TimeDelayOff, float TimeDelayOn) {
  _input = Input;
  this->SetTimeDelay(TimeDelayOff, TimeDelayOn);
  return this->_Blink();
}

float MicroBeaut_Blink::GetTimeDelayOn(void) {
  return ((float)_timeDelayOn * 0.000001);
}

float MicroBeaut_Blink::GetTimeDelayOff(void) {
  return ((float)_timeDelayOff * 0.000001);
}

float MicroBeaut_Blink::GetElapsedTime(void) {
  return ((float)_elapsedTime * 0.000001);
}

bool MicroBeaut_Blink::_Blink(void) {
  if (_input) {

    if (!_prevInput) {
      _prevTime = micros();
    }
    _currTime = micros();
    _elapsedTime += (_currTime - _prevTime);
    if (_output) {
      if (_elapsedTime >= _timeDelayOn ) {
        if (0UL < _timeDelayOff ) {
          _output = false;
          _elapsedTime = _elapsedTime - _timeDelayOn;
          if (_elapsedTime >= _timeDelayOn ) {
            _elapsedTime = 0UL;
          }
        }
        else {
          _elapsedTime = _timeDelayOn;
        }
      }
    }
    else {
      if (_elapsedTime >= _timeDelayOff) {
        if (0UL < _timeDelayOn ) {
          _output = true;
          _elapsedTime = _elapsedTime - _timeDelayOff;
          if (_elapsedTime >= _timeDelayOff ) {
            _elapsedTime = 0UL;
          }
        }
        else {
          _elapsedTime = _timeDelayOff;
        }
      }
    }
    _prevTime = _currTime;
  }
  _prevInput = _input;
  return _output;
}

bool MicroBeaut_Blink::Output(void) {
  return _output;
}


/*
  ===========================================================================
  Function: TimePulse
  Purpose:  Time Pulse.

  Generate a pulse of duration "TimeDelay" starting on the rising edge of input
  ===========================================================================
*/
MicroBeaut_TimePulse::MicroBeaut_TimePulse(void) {
  _input = false;
  _reset = false;
  _prevInput = false;
}

void MicroBeaut_TimePulse::SetTimeDelay(float TimeDelay) {
  _timeDelay = TimeDelay * 1000000.0;
}

bool MicroBeaut_TimePulse::TimePulse(bool Input) {
  _input = Input;
  return this->_TimePulse();
}

bool MicroBeaut_TimePulse::TimePulse(bool Input, float TimeDelay) {
  _input = Input;
  this->SetTimeDelay(TimeDelay);
  return this->_TimePulse();
}

float MicroBeaut_TimePulse::GetTimeDelay(void) {
  return ((float)_timeDelay * 0.000001);
}

float MicroBeaut_TimePulse::GetElapsedTime(void) {
  return ((float)_elapsedTime * 0.000001);
}

bool MicroBeaut_TimePulse::_TimePulse(void) {

  if (!_output) {
    if (_input & !_prevInput) {
      _output = true;
      _prveTime = micros();
    }
    if (!_input) {
      _elapsedTime = 0UL;
    }
  }
  else {
    _elapsedTime = micros() - _prveTime;
    if (_elapsedTime >= _timeDelay) {
      _elapsedTime = _timeDelay;
      _output = false;
    }
  }
  _prevInput = _input;
  return _output;
}

bool MicroBeaut_TimePulse::Output(void) {
  return _output;
}



/*
  ===========================================================================
  Function: Trigger
  Purpose:  Trigger.

  The rising edge of input "Input" starts a timer of duration "TimeDelay".
  When the elapsed time is greater than or equal to "TimeDelay",
  the timer restart and output changes from FALSE to TRUE one scan.
  The output does not change if "Input" is FALSE.
  ===========================================================================
*/

MicroBeaut_Trigger::MicroBeaut_Trigger(void) {
  _input = false;
  _prevInput = false;
}

void MicroBeaut_Trigger::SetTimeDelay(float TimeDelay) {
  _timeDelay = TimeDelay * 1000000.0;
}

bool MicroBeaut_Trigger::Trigger(bool Input) {
  _input = Input;
  return this->_Trigger();
}

bool MicroBeaut_Trigger::Trigger(bool Input, bool Reset) {
  _input = Input;
  _reset = Reset;
  return this->_Trigger();
}

bool MicroBeaut_Trigger::Trigger(bool Input, bool Reset, float TimeDelay) {
  _input = Input;
  _reset = Reset;
  this->SetTimeDelay(TimeDelay);
  return this->_Trigger();
}

float MicroBeaut_Trigger::GetTimeDelay(void) {
  return ((float)_timeDelay * 0.000001);
}

float MicroBeaut_Trigger::GetElapsedTime(void) {
  return ((float)_elapsedTime * 0.000001);
}

bool MicroBeaut_Trigger::_Trigger(void) {
  if (_reset) {
    _output = false;
    _elapsedTime = 0UL;
  }
  else {
    if (_input) {
      if (!_prevInput) {
        _prveTime = micros();
      }
      _currTime = micros();
      _elapsedTime += _currTime - _prveTime;
      if ( _elapsedTime >= _timeDelay) {
        _output  = true ;
        _elapsedTime = _elapsedTime - _timeDelay;
        if (_elapsedTime >= _timeDelay ) {
          _elapsedTime = 0UL;
        }
      }
      else {
        _output  = false ;
      }
    }
    _prveTime  = _currTime ;
  }
  _prevInput = _input & !_reset;
  return _output;
}

bool MicroBeaut_Trigger::Output(void) {
  return _output;
}



/*
  ===========================================================================
  Function:  TimeSchedule
  Purpose:   Schedule execution at specified time intervals.

  Function TimeScedule schedules the execution of certain routines at
  desired time intervals. Output is TRUE when the specified "period."
  of time has passed, holding TRUE for one scan; otherwise, output Output is FALSE.
  By testing the output Output, you can cause sections of the control program
  to be executed periodically.

  ===========================================================================
*/

MicroBeaut_TimeSchedule::MicroBeaut_TimeSchedule(void) {
  _input = false;
  _output = false;
  _timeSchedule = 10000UL;
}


bool MicroBeaut_TimeSchedule::Run(bool enableInput, float TimeSchedule, MicroBeaut_CallBackFunction FunctionName) {
  this->Setup(TimeSchedule, FunctionName);
  return this->Run(enableInput);
}

void MicroBeaut_TimeSchedule::Setup(float TimeSchedule, MicroBeaut_CallBackFunction FunctionName) {
  _timeSchedule = TimeSchedule * 1000000UL;
  _callBackFunction = FunctionName;
}

bool MicroBeaut_TimeSchedule::Run(bool enableInput) {
  _input = enableInput;
  return this->_Run();
}

bool MicroBeaut_TimeSchedule::_Run() {
  if (_input) {
    if (!_prevInput) {
      _prveTime = micros();
    }
    _currTime = micros();
    _elapsedTime += (_currTime - _prveTime);
    if ( _elapsedTime >= _timeSchedule) {
      _actual = _elapsedTime;
      _elapsedTime = _elapsedTime - _timeSchedule;
      _output  = true ;
      if ( _elapsedTime >= _timeSchedule) {
        _elapsedTime = 0UL;
      }
      _callBackFunction ();
    }
    else {
      _output  = false ;
    }
    _prveTime = _currTime;
  }
  _prevInput = _input;
  return _output;
}

float MicroBeaut_TimeSchedule::Actual(void) {
  return (float)_actual * 0.000001;
}

bool MicroBeaut_TimeSchedule::Output(void) {
  return _output;
}



/*
  ===========================================================================
  Function:  ScanSchedule
  Purpose:   Schedules execution after a certain number of scans.

  This function can schedule the execution of certain routines when
  a specified number of evaluations has occurred. Output
  is TRUE after the specified number of evaluations, holding TRUE for one
  evaluation. By testing the output, you can cause sections of the
  control program to be executed periodically.
  ===========================================================================
*/


MicroBeaut_ScanSchedule::MicroBeaut_ScanSchedule(void) {
  _input = false;
  _output = false;
  _currNumberOfScan = 0UL;
}


bool MicroBeaut_ScanSchedule::Run(bool enableInput, unsigned long NumberOfScan, MicroBeaut_CallBackFunction FunctionName) {
  this->Setup(NumberOfScan, FunctionName);
  return this->Run(enableInput);
}

void MicroBeaut_ScanSchedule::Setup(unsigned long NumberOfScan, MicroBeaut_CallBackFunction FunctionName) {
  _numberOfScan = NumberOfScan;
  _callBackFunction = FunctionName;
}

bool MicroBeaut_ScanSchedule::Run(bool enableInput) {
  _input = enableInput;
  return this->_Run();
}

bool MicroBeaut_ScanSchedule::_Run() {
  if (_input) {
    if (!_prevInput) {
      _prveTime = micros();
    }
    _currTime = micros();
    _elapsedTime += (_currTime - _prveTime);
    _currNumberOfScan++;
    if ( _currNumberOfScan >= _numberOfScan) {
      _currNumberOfScan = 0UL;
      _actual = _elapsedTime;
      _elapsedTime = 0UL;
      _output  = true ;
      _callBackFunction ();
    }
    else {
      _output  = false ;
    }
    _prveTime = _currTime;
  }
  _prevInput = _input;
  return _output;
}

float MicroBeaut_ScanSchedule::Actual(void) {
  return (float)_actual * 0.000001;
}

bool MicroBeaut_ScanSchedule::Output(void) {
  return _output;
}