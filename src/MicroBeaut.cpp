#include "MicroBeaut.h"
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



/*
  ===========================================================================
  Function:  SR
  Purpose:  Set Dominant

  Function SR is a set dominant latch. The set input sets the
  latch. The reset input resets the latch if the set input is FALSE.

  ===========================================================================
*/
MicroBeaut_SR::MicroBeaut_SR(void) {}

bool MicroBeaut_SR::SR(bool setInput, bool resetInput) {
  _output = setInput | (!resetInput & _output);
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
MicroBeaut_RS::MicroBeaut_RS(void) {}

bool MicroBeaut_RS::RS(bool setInput, bool resetInput) {
  _output = (setInput | _output) & !resetInput;
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
MicroBeaut_Toggle::MicroBeaut_Toggle(void) {}

bool MicroBeaut_Toggle::Toggle(bool toggleInput, bool resetInput) {
  _output = (_output ^ (toggleInput & !_prevInput)) & !resetInput;
  _prevInput = toggleInput;
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
MicroBeaut_Rising::MicroBeaut_Rising(void) {}

bool MicroBeaut_Rising::Rising(bool risingInput)
{
  _output = risingInput & !_prevInput;
  _prevInput = risingInput;
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
MicroBeaut_Falling::MicroBeaut_Falling(void) {}

bool MicroBeaut_Falling::Falling(bool fallingInput)
{
  _output = !fallingInput & _prevInput;
  _prevInput = fallingInput;
  return _output;
}

bool MicroBeaut_Falling::Output(void) {
  return _output;
}



/*
  ===========================================================================
  Function:  Debounce
  Purpose:   Debounce.

  The rising edge of input "bounceInput" starts a timer of duration "timeDebounce".
  When the elapsed time is greater than or equal to "timeDebounce",
  the timer stops and output changes from FALSE to TRUE.

  The falling edge of input "bounceInput" starts a timer of duration "timeDebounce".
  When the elapsed time is greater than or equal to "timeDebounce",
  the timer stops and output changes from TRUE to FALSE.
  ===========================================================================
*/
MicroBeaut_Debounce::MicroBeaut_Debounce(void) {}

void MicroBeaut_Debounce::SetTimeDebounce(float timeDebounce) {
  _timeDebounce = timeDebounce * 1000000.0;
}

bool MicroBeaut_Debounce::Debounce(bool bounceInput) {
  if (bounceInput != _prevInput) {
    _prveTime = micros();
  }
  if (bounceInput != _output) {
    _elapsedTime = micros() - _prveTime;
    if (_elapsedTime >= _timeDebounce) {
      _output = bounceInput;
      _elapsedTime = _timeDebounce;
    }
  }
  else {
    _elapsedTime = 0UL;
  }
  _prevInput = bounceInput;
  return _output;
}

float MicroBeaut_Debounce::GetTimeDebounce(void) {
  return ((float)_timeDebounce * 0.000001);
}

float MicroBeaut_Debounce::GetElapsedTime(void) {
  return ((float)_elapsedTime * 0.000001);
}

bool MicroBeaut_Debounce::Output(void) {
  return _output;
}



/*
  ===========================================================================
  Function: TimerOn
  Purpose:  Timer On

  The rising edge of input "timerOnInput" starts a timer of duration "timeDelay".
  When the elapsed time is greater than or equal to "timeDelay",
  the timer stops and output changes from FALSE to TRUE.
  The next falling edge of input "timerOnInput" initializes the timer
  ===========================================================================
*/
MicroBeaut_TimerOn::MicroBeaut_TimerOn(void) {}

void MicroBeaut_TimerOn::SetTimeDelay(float timeDelay) {
  _timeDelay = timeDelay * 1000000.0;
}

bool MicroBeaut_TimerOn::TimerOn(bool timerOnInput) {
  if (timerOnInput) {
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
  _prevInput = timerOnInput;
  return _output;
}

bool MicroBeaut_TimerOn::Output(void) {
  return _output;
}

float MicroBeaut_TimerOn::GetTimeDelay(void) {
  return ((float)_timeDelay * 0.000001);
}

float MicroBeaut_TimerOn::GetElapsedTime(void) {
  return ((float)_elapsedTime * 0.000001);
}



/*
  ===========================================================================
  Function: TimerOff
  Purpose:  Timer Off.

  The falling edge of input "timerOffInput" starts a timer of duration "timeDelay".
  When the elapsed time is greater than or equal to "timeDelay",
  the timer stops and output changes from TRUE to FALSE.
  If input "timerOffInput" is TRUE, then TimerOff sets output to TRUE and the elapsed time to zero.
  ===========================================================================
*/
MicroBeaut_TimerOff::MicroBeaut_TimerOff(void) {}

void MicroBeaut_TimerOff::SetTimeDelay(float timeDelay) {
  _timeDelay = timeDelay * 1000000.0;
}

bool MicroBeaut_TimerOff::TimerOff(bool timerOffInput) {
  if (timerOffInput) {
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
  _prevInput = timerOffInput;
  return _output;
}

bool MicroBeaut_TimerOff::Output(void) {
  return _output;
}

float MicroBeaut_TimerOff::GetTimeDelay(void) {
  return ((float)_timeDelay * 0.000001);
}

float MicroBeaut_TimerOff::GetElapsedTime(void) {
  return ((float)_elapsedTime * 0.000001);
}



/*
  ===========================================================================
  Function: Blink
  Purpose:  Blink.

  Input "enableInput" enables blinking. Input "timeDelayOn" gives the minimum time that the output is TRUE.
  Input "TimeDelayrOff" gives the minimum time that the output is FALSE.
  The output does not change if "Input" is FALSE.
  ===========================================================================
*/
MicroBeaut_Blink::MicroBeaut_Blink(void) {}

void MicroBeaut_Blink::SetTimeDelay(float timeDelayOff, float timeDelayOn) {
  _timeDelayOff = timeDelayOff * 1000000.0;
  _timeDelayOn = timeDelayOn * 1000000.0;
}

bool MicroBeaut_Blink::Blink(bool enableInput) {
  if (enableInput) {

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
    _prevInput = enableInput;
  }
  return _output;
}

bool MicroBeaut_Blink::Output(void) {
  return _output;
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



/*
  ===========================================================================
  Function: TimePulse
  Purpose:  Time Pulse.

  Generate a pulse of duration "timeDelay" starting on the rising edge of input
  ===========================================================================
*/
MicroBeaut_TimePulse::MicroBeaut_TimePulse(void) {}

void MicroBeaut_TimePulse::SetTimeDelay(float timeDelay) {
  _timeDelay = timeDelay * 1000000.0;
}

bool MicroBeaut_TimePulse::TimePulse(bool pulseInput) {

  if (!_output) {
    if (pulseInput & !_prevInput) {
      _output = true;
      _prveTime = micros();
    }
    if (!pulseInput) {
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
  _prevInput = pulseInput;
  return _output;
}

bool MicroBeaut_TimePulse::Output(void) {
  return _output;
}

float MicroBeaut_TimePulse::GetTimeDelay(void) {
  return ((float)_timeDelay * 0.000001);
}

float MicroBeaut_TimePulse::GetElapsedTime(void) {
  return ((float)_elapsedTime * 0.000001);
}



/*
  ===========================================================================
  Function: Trigger
  Purpose:  Trigger.

  The rising edge of input "enableInput" starts a timer of duration "timeDelay".
  When the elapsed time is greater than or equal to "timeDelay",
  the timer restart and output changes from FALSE to TRUE one scan.
  The output does not change if "enableInput" is FALSE.
  ===========================================================================
*/
MicroBeaut_Trigger::MicroBeaut_Trigger(void) {}

void MicroBeaut_Trigger::SetTimeDelay(float timeDelay) {
  _timeDelay = timeDelay * 1000000.0;
}

bool MicroBeaut_Trigger::Trigger(bool enableInput, bool resetInput) {
  if (resetInput) {
    _output = false;
    _elapsedTime = 0UL;
  }
  else {
    if (enableInput) {
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
  _prevInput = enableInput & !resetInput;
  return _output;
}

bool MicroBeaut_Trigger::Output(void) {
  return _output;
}

float MicroBeaut_Trigger::GetTimeDelay(void) {
  return ((float)_timeDelay * 0.000001);
}

float MicroBeaut_Trigger::GetElapsedTime(void) {
  return ((float)_elapsedTime * 0.000001);
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
MicroBeaut_TimeSchedule::MicroBeaut_TimeSchedule(void) {}

void MicroBeaut_TimeSchedule::Config(float timeSchedule, MicroBeaut_CallBackFunction functionName) {
  _timeSchedule = timeSchedule * 1000000UL;
  _callBackFunction = functionName;
}

bool MicroBeaut_TimeSchedule::Run(bool enableInput) {
  if (enableInput) {
    if (!_prevEnable) {
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
  _prevEnable = enableInput;
  return _output;
}

float MicroBeaut_TimeSchedule::Actual(void) {
  return (float)_actual * 0.000001;
}

bool MicroBeaut_TimeSchedule::Output() {
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

MicroBeaut_ScanSchedule::MicroBeaut_ScanSchedule(void) {}

void MicroBeaut_ScanSchedule::Config(unsigned long numberOfScan, MicroBeaut_CallBackFunction functionName) {
  _numberOfScan = numberOfScan;
  _callBackFunction = functionName;
}

bool MicroBeaut_ScanSchedule::Run(bool enableInput) {
  if (enableInput) {
    if (!_prevEnable) {
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
  _prevEnable = enableInput;
  return _output;
}

float MicroBeaut_ScanSchedule::Actual(void) {
  return (float)_actual * 0.000001;
}

bool MicroBeaut_ScanSchedule::Output(void) {
  return _output;
}