/*
  ===========================================================================
  Function: readInput
  Purpose:  Time Pulse.

  Generate a pulse of duration "msTimeDelay" starting on the rising edge of input
  ===========================================================================
*/

#include "TimePulse.h"

MicroBeaut_TimePulse::MicroBeaut_TimePulse() {
  _output = false;
}

void MicroBeaut_TimePulse::setTimeDelay(uint16_t msTimeDelay) {
  _usTimeDelay = (unsigned long)msTimeDelay * 1000.0;
}

bool MicroBeaut_TimePulse::readInput(bool input) {

  if (!_output) {
    if (input & !_prevInput) {
      _output = true;
      _prevTime = micros();
    }
    if (!input) {
      _usElapsedTime = 0UL;
    }
  }
  else {
    _usElapsedTime = micros() - _prevTime;
    if (_usElapsedTime >= _usTimeDelay) {
      _usElapsedTime = _usTimeDelay;
      _output = false;
    }
  }
  _prevInput = input;
  return _output;
}

bool MicroBeaut_TimePulse::readStatus() {
  return _output;
}

uint16_t MicroBeaut_TimePulse::getTimeDelay() {
  return (uint16_t)(_usTimeDelay * 0.001);
}

uint16_t MicroBeaut_TimePulse::getElapsedTime() {
  return (uint16_t)(_usElapsedTime * 0.001);
}