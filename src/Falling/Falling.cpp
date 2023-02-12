/*
  ===========================================================================
  Function:    readInput
  Purpose:     falling Edge Detector

  Set readStatus on the falling edge of Input.
  ===========================================================================
*/

#include "Falling.h"

MicroBeaut_Falling::MicroBeaut_Falling() {
  _output = false;
}

bool MicroBeaut_Falling::readInput(bool input)
{
  _output = !input & _prevInput;
  _prevInput = input;
  return _output;
}

bool MicroBeaut_Falling::readStatus() {
  return _output;
}