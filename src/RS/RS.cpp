/*
  ===========================================================================
  Function: readInput
  Purpose:  Reset Dominant

  Function readInput is a reset dominant latch. The reset input resets the
  latch. The set input sets the latch if the reset input is FALSE.

  ===========================================================================
*/

#include "RS.h"

MicroBeaut_RS::MicroBeaut_RS() {
  _output = false;
}

bool MicroBeaut_RS::readInput(bool input, bool reset) {
  _output = (input | _output) & !reset;
  return _output;
}

bool MicroBeaut_RS::readStatus() {
  return _output;
}