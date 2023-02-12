/*
  ===========================================================================
  Function:  SR
  Purpose:  Set Dominant

  Function SR is a set dominant latch. The set input sets the
  latch. The reset input resets the latch if the set input is FALSE.

  ===========================================================================
*/

#include "SR.h"

MicroBeaut_SR::MicroBeaut_SR() {
    _output = false;
}

bool MicroBeaut_SR::readInput(bool input, bool reset) {
  _output = input | (!reset & _output);
  return _output;
}

bool MicroBeaut_SR::readStatus() {
  return _output;
}