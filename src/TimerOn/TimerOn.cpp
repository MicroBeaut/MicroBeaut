
/*
  ===========================================================================
  Function: readInput
  Purpose:  Timer On

  The rising edge of input "input" starts a timer of duration "timeDelay".
  When the elapsed time is greater than or equal to "timeDelay",
  the timer stops and output changes from FALSE to TRUE.
  The next falling edge of input "input" initializes the timer
  ===========================================================================
*/

#include "TimerOn.h"

MicroBeaut_TimerOn::MicroBeaut_TimerOn() {
  _output = false;
}

void MicroBeaut_TimerOn::setTimeDelay(uint16_t msTimeDelay) {
  _usTimeDelay = (unsigned long)msTimeDelay * 1000.0;
}

bool MicroBeaut_TimerOn::readInput(bool input) {
  if (input) {
    if (!_prevInput) {
      _prevTime = micros();
    }
    _usElapsedTime = micros() - _prevTime;
    if (_usElapsedTime >= _usTimeDelay) {
      _output = true;
      _usElapsedTime = _usTimeDelay;
    }
  }
  else {
    _output = false;
    _usElapsedTime = 0UL;
  }
  _prevInput = input;
  return _output;
}

bool MicroBeaut_TimerOn::readStatus() {
  return _output;
}

uint16_t MicroBeaut_TimerOn::getTimeDelay() {
  return (uint16_t)(_usTimeDelay * 0.001);
}

uint16_t MicroBeaut_TimerOn::getElapsedTime() {
  return (uint16_t)(_usElapsedTime * 0.001);
}