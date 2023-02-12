/*
  ===========================================================================
  Function: readInput
  Purpose:  readInput.

  The rising edge of input "input" starts a timer of duration "msTimeDelay".
  When the elapsed time is greater than or equal to "msTimeDelay",
  the timer restart and output changes from FALSE to TRUE one scan.
  The output does not change if "input" is FALSE.
  ===========================================================================
*/

#include "Trigger.h"

MicroBeaut_Trigger::MicroBeaut_Trigger() {
  _output = false;
}

void MicroBeaut_Trigger::setTimeDelay(uint16_t msTimeDelay) {
  _usTimeDelay = (unsigned long)msTimeDelay * 1000.0;
}

bool MicroBeaut_Trigger::readInput(bool input, bool reset) {
  if (reset) {
    _output = false;
    _usElapsedTime = 0UL;
  }
  else {
    if (input) {
      if (!_prevInput) {
        _prevTime = micros();
      }
      _currTime = micros();
      _usElapsedTime += _currTime - _prevTime;
      if ( _usElapsedTime >= _usTimeDelay) {
        _output  = true ;
        _usElapsedTime = _usElapsedTime - _usTimeDelay;
        if (_usElapsedTime >= _usTimeDelay ) {
          _usElapsedTime = 0UL;
        }
      }
      else {
        _output  = false ;
      }
    }
    _prevTime  = _currTime ;
  }
  _prevInput = input & !reset;
  return _output;
}

bool MicroBeaut_Trigger::readStatus() {
  return _output;
}

uint16_t MicroBeaut_Trigger::getTimeDelay() {
  return (uint16_t)(_usTimeDelay * 0.001);
}

uint16_t MicroBeaut_Trigger::getElapsedTime() {
  return (uint16_t)(_usElapsedTime * 0.001);
}