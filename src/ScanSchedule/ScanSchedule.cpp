/*
  ===========================================================================
  Function:  ScanSchedule
  Purpose:   Schedules execution after a certain number of scans.

  This function can schedule the execution of certain routines when
  a specified number of evaluations has occurred. readStatus
  is TRUE after the specified number of evaluations, holding TRUE for one
  evaluation. By testing the output, you can cause sections of the
  control program to be executed periodically.
  ===========================================================================
*/

#include "ScanSchedule.h"

MicroBeaut_ScanSchedule::MicroBeaut_ScanSchedule() {
  _prevEnable = false;
  _output = false;
}

void MicroBeaut_ScanSchedule::setScanSchedule(unsigned long numberOfScan, MicroBeaut_CallBackFunction functionName) {
  _numberOfScan = numberOfScan;
  _callBackFunction = functionName;
}

bool MicroBeaut_ScanSchedule::readInput(bool enable) {
  if (enable) {
    if (!_prevEnable) {
      _prevTime = micros();
    }
    _currTime = micros();
    _usElapsedTime += (_currTime - _prevTime);
    _currNumberOfScan++;
    if ( _currNumberOfScan >= _numberOfScan) {
      _currNumberOfScan = 0UL;
      _actual = _usElapsedTime;
      _usElapsedTime = 0UL;
      _output  = true ;
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

uint16_t MicroBeaut_ScanSchedule::getElapsedTime() {
  return (uint16_t)_actual * 0.001;
}

bool MicroBeaut_ScanSchedule::readStatus() {
  return _output;
}