/*
  ===========================================================================
  Function: readInput
  Purpose:  Timer Off.

  The falling edge of input "input" starts a timer of duration "msTimeDelay".
  When the elapsed time is greater than or equal to "msTimeDelay",
  the timer stops and output changes from TRUE to FALSE.
  If input "input" is TRUE, then readInput sets output to TRUE and the elapsed time to zero.
  ===========================================================================
*/

#include "TimerOff.h"

MicroBeaut_TimerOff::MicroBeaut_TimerOff() {}

void MicroBeaut_TimerOff::setTimeDelay(uint16_t msTimeDelay) {
  _usTimeDelay = (unsigned long)msTimeDelay * 1000.0;
}

bool MicroBeaut_TimerOff::readInput(bool input) {
  if (input) {
    _output = true;
    _usElapsedTime = 0UL;
  }
  else {
    if (_prevInput) {
      _prevTime = micros();
    }
    _usElapsedTime =  micros() - _prevTime;
    if (_usElapsedTime >= _usTimeDelay) {
      _output = false;
      _usElapsedTime = _usTimeDelay;
    }
  }
  _prevInput = input;
  return _output;
}

bool MicroBeaut_TimerOff::readStatus() {
  return _output;
}

uint16_t MicroBeaut_TimerOff::getTimeDelay() {
  return ((uint16_t)_usTimeDelay * 0.001);
}

uint16_t MicroBeaut_TimerOff::getElapsedTime() {
  return ((uint16_t)_usElapsedTime * 0.001);
}