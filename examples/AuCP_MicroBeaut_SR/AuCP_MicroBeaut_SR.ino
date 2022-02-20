/*
  -- ========================================================
  -- Subject: Applied Microcontroller Programming (AuCP)
  -- Purpose: Applied PLC Function to MCU.
  -- Author:  Montree Hamarn
  -- GitHub:  https://github.com/MicroBeaut
  -- YouTube: What Did You Learn Today
  --          https://www.youtube.com/playlist?list=PLFf3xtcn9d47akU0G3bf2BXiMebCzrvMm
  -- ========================================================
*/
/*
  -- ===========================================================================
  Function: SR (Set Dominante)

  Function SR is a Set Dominant latch. The set input sets the
  latch. The reset input resets the latch if the set input is FALSE.

  Member:
  Microbeaut_SR(void);
  bool SR(bool Input, bool Reset);

  Declaration:
  Microbeaut_SR variableName

  Parameters:
  Input:
    Set             : Set Input
    Reset           : Reset Input

  Return:
    TRUE or FALSE (HIGH/LOW)


  Syntax:
    boolVariable = variableName.SR(boolInput, boolReset);

*/
// https://wokwi.com/arduino/projects/324015704281973332

#include "MicroBeaut.h"

#define swSetPin      A0         // Define Push Button Pin
#define swResetPin    A1         // Define Push Button Pin
#define ledSetPin     7          // Degine LED Pin
#define ledResetPin   6          // Degine LED Pin
#define ledOutputPin  5          // Degine LED Pin

MicroBeaut_SR srOutput;         // SR Variable
bool swSetState;                // Input State
bool swResetState;              // Input State
bool ledOutputState;            // Output State

// Latching Purposes
MicroBeaut_Toggle togSet;       // Toggle Vareiable
MicroBeaut_Toggle togReset;     // Toggle Vareiable
bool setState;                  // Toggle State
bool resetState;                // Toggle State


// Printing Purpose
MicroBeaut_Trigger triggerDisplay;    // Toggle Variable
unsigned long lineNumber;             // Line Number : Max = 9999
const float printPresetTime = 0.25;   // 250 milliseconds


void setup() {
  Serial.begin(115200);                           // Set Buad Rate
  triggerDisplay.SetTimeDelay(printPresetTime);   // Initial Time Delay for Printing

  pinMode(swSetPin, INPUT);               // Input Pin Mode
  pinMode(swResetPin, INPUT);             // Input Pin Mode
  pinMode(ledSetPin, OUTPUT);             // Output Pin Mode
  pinMode(ledResetPin, OUTPUT);           // Output Pin Mode
  pinMode(ledOutputPin, OUTPUT);          // Output Pin Mode
}

void loop() {

  swSetState = digitalRead(swSetPin);         // Read Input State (0 = Release, 1 = Press)
  setState = togSet.Toggle(swSetState);       // Toggle Function with Input Parameter
  digitalWrite(ledSetPin, setState);          // ON/OFF LED

  swResetState = digitalRead(swResetPin);     // Read Input State (0 = Release, 1 = Press)
  resetState = togReset.Toggle(swResetState); // Toggle Function with Input Parameter
  digitalWrite(ledResetPin, resetState);      // ON/OFF LED

  // To Test SR Function
  ledOutputState = srOutput.SR(setState, resetState); // SR Function with Ser/Reset Parameter
  digitalWrite(ledOutputPin, ledOutputState);         // ON/OFF LED

  // Toggle for Printing
  if (triggerDisplay.Trigger(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;       // Compare / Increase / Reset Line Number
    Serial.println("L" + String(lineNumber)
                   + " Set: " + String(setState)               // Set State
                   + ", Reset: " + String(resetState)          // Reset State
                   + ", Output: " + String(ledOutputState * 2)); // Output State x2 for Monitor S/R Input on Serial Plotter
  }
}