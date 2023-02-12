/*
  ===========================================================================
  Function: readInput
  Purpose:  readInput.

  Input "enable" enables blinking. Input "msTimeDelayOn" gives the minimum time that the output is TRUE.
  Input "TimeDelayrOff" gives the minimum time that the output is FALSE.
  The output does not change if "Input" is FALSE.
  ===========================================================================
*/

#include "Blink.h"

MicroBeaut_Blink::MicroBeaut_Blink() {
  _prevInput = false;
  _output = false;
}

void MicroBeaut_Blink::setTimeDelay(uint16_t msTimeDelayOff, uint16_t msTimeDelayOn) {
  _timeDelayOff = (unsigned long)msTimeDelayOff * 1000.0;
  _timeDelayOn = (unsigned long)msTimeDelayOn * 1000.0;
}

bool MicroBeaut_Blink::readInput(bool enable) {
  if (enable) {
    if (!_prevInput) {
      _prevTime = micros();
    }
    _currTime = micros();
    _usElapsedTime += (_currTime - _prevTime);
    if (_output) {
      if (_usElapsedTime >= _timeDelayOn ) {
        if (0UL < _timeDelayOff ) {
          _output = false;
          _usElapsedTime = _usElapsedTime - _timeDelayOn;
          if (_usElapsedTime >= _timeDelayOn ) {
            _usElapsedTime = 0UL;
          }
        }
        else {
          _usElapsedTime = _timeDelayOn;
        }
      }
    }
    else {
      if (_usElapsedTime >= _timeDelayOff) {
        if (0UL < _timeDelayOn ) {
          _output = true;
          _usElapsedTime = _usElapsedTime - _timeDelayOff;
          if (_usElapsedTime >= _timeDelayOff ) {
            _usElapsedTime = 0UL;
          }
        }
        else {
          _usElapsedTime = _timeDelayOff;
        }
      }
    }
    _prevTime = _currTime;
    _prevInput = enable;
  }
  return _output;
}

bool MicroBeaut_Blink::readStatus() {
  return _output;
}

uint16_t MicroBeaut_Blink::getTimeDelayOn() {
  return (uint16_t)(_timeDelayOn * 0.001);
}

uint16_t MicroBeaut_Blink::getTimeDelayOff() {
  return (uint16_t)(_timeDelayOff * 0.001);
}

uint16_t MicroBeaut_Blink::getElapsedTime() {
  return (uint16_t)(_usElapsedTime * 0.001);
}