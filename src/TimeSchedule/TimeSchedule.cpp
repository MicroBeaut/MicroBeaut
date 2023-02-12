/*
  ===========================================================================
  Function:  TimeSchedule
  Purpose:   Schedule execution at specified time intervals.

  Function TimeScedule schedules the execution of certain routines at
  desired time intervals. readStatus is TRUE when the specified "period."
  of time has passed, holding TRUE for one scan; otherwise, output readStatus is FALSE.
  By testing the output readStatus, you can cause sections of the control program
  to be executed periodically.

  ===========================================================================
*/

#include "TimeSchedule.h"

MicroBeaut_TimeSchedule::MicroBeaut_TimeSchedule() {
  _prevEnable = false;
  _output = false;
}

void MicroBeaut_TimeSchedule::setTimeSchedule(uint16_t msTimeSchedule, MicroBeaut_CallBackFunction functionName) {
  _timeSchedule = (unsigned long)msTimeSchedule * 1000UL;
  _callBackFunction = functionName;
}

bool MicroBeaut_TimeSchedule::readInput(bool enable) {
  if (enable) {
    if (!_prevEnable) {
      _prevTime = micros();
    }
    _currTime = micros();
    _usElapsedTime += (_currTime - _prevTime);
    if ( _usElapsedTime >= _timeSchedule) {
      _actual = _usElapsedTime;
      _usElapsedTime = _usElapsedTime - _timeSchedule;
      _output  = true ;
      if ( _usElapsedTime >= _timeSchedule) {
        _usElapsedTime = 0UL;
      }
      if(_callBackFunction) {
        _callBackFunction ();
      }
    }
    else {
      _output  = false ;
    }
    _prevTime = _currTime;
  }
  _prevEnable = enable;
  return _output;
}

uint16_t MicroBeaut_TimeSchedule::getElapsedTime() {
  return (uint16_t)_actual * 0.001;
}

bool MicroBeaut_TimeSchedule::readStatus() {
  return _output;
}