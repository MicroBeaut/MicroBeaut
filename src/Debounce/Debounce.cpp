/*
  ===========================================================================
  Function:  readInput
  Purpose:   readInput.

  The rising edge of input "input" starts a timer of duration "timeDebounce".
  When the elapsed time is greater than or equal to "timeDebounce",
  the timer stops and output changes from FALSE to TRUE.

  The falling edge of input "input" starts a timer of duration "timeDebounce".
  When the elapsed time is greater than or equal to "timeDebounce",
  the timer stops and output changes from TRUE to FALSE.
  ===========================================================================
*/
#include "Debounce.h"

MicroBeaut_Debounce::MicroBeaut_Debounce() {
  _output = false;
}

void MicroBeaut_Debounce::setTimeDebounce(uint16_t msTimeDebounce) {
  _usTimeDebounce = (unsigned long)msTimeDebounce * 1000.0;
}

bool MicroBeaut_Debounce::readInput(bool input) {
  if (input != _prevInput) {
    _prevTime = micros();
  }
  if (input != _output) {
    _usElapsedTime = micros() - _prevTime;
    if (_usElapsedTime >= _usTimeDebounce) {
      _output = input;
      _usElapsedTime = _usTimeDebounce;
    }
  }
  else {
    _usElapsedTime = 0UL;
  }
  _prevInput = input;
  return _output;
}

uint16_t MicroBeaut_Debounce::getTimeDebounce() {
  return (uint16_t)(_usTimeDebounce * 0.001);
}

uint16_t MicroBeaut_Debounce::getElapsedTime() {
  return (uint16_t)(_usElapsedTime * 0.001);
}

bool MicroBeaut_Debounce::readStatus() {
  return _output;
}