/*
  ===========================================================================
  Function:  Toggle
  Purpose:   Toggle.

  The rising edge of input "Input" toggles readStatus.
  Input "Reset" resets readStatus (to FALSE).
  ===========================================================================
*/

#include "Toggle.h"

MicroBeaut_Toggle::MicroBeaut_Toggle() {
  _output = false;
}

bool MicroBeaut_Toggle::readInput(bool input, bool reset) {
  _output = (_output ^ (input & !_prevInput)) & !reset;
  _prevInput = input;
  return _output;
}

bool MicroBeaut_Toggle::readStatus() {
  return _output;
}