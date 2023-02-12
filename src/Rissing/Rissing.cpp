/*
  ===========================================================================
  Function: readInput
  Purpose:  Falling Edge
 Detector

  Set readStatus on the rising edge of Input.
  ===========================================================================
*/

#include "Rissing.h"

MicroBeaut_Rising::MicroBeaut_Rising() {
  _output = false;
}

bool MicroBeaut_Rising::readInput(bool input)
{
  _output = input & !_prevInput;
  _prevInput = input;
  return _output;
}

bool MicroBeaut_Rising::readStatus() {
  return _output;
}