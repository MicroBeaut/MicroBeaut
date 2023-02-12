/*
  -- ========================================================
  -- Subject: Applied Microcontroller Programming (AuCP)
  -- Purpose: Applied PLC Function to MCU.
  -- Author:  Montree Hamarn, Natvalun Tavepontakul
  -- Email:   montree.hamarn@gmail.com, natvalun.tavepontakul@hotmail.com
  -- GitHub:  https://github.com/MicroBeaut
  -- YouTube: What Did You Learn Today
  --          https://www.youtube.com/playlist?list=PLFf3xtcn9d47akU0G3bf2BXiMebCzrvMm
  -- ========================================================
*/
/*
  -- ===========================================================================
  Function: SR (Set Dominant)

  Function SR is a Set Dominant latch. The set input sets the
  latch. The reset input resets the latch if the set input is FALSE.

  Member:
  Microbeaut_SR(void);
  bool SR(bool setInput, bool resetInput);

  Declaration:
  Microbeaut_SR variableName

  Parameters:
  Input:
  Set             : Set Input
  Reset           : Reset Input

  Return:
  TRUE or FALSE (HIGH/LOW)

  Get Output/Parameters:
  boolVariable = variableName.readStatus();

  Syntax:
  boolVariable = variableName.SR(boolSet, boolReset);

*/
// WokWi: https://wokwi.com/arduino/projects/324015704281973332

#include "MicroBeaut.h"

#define setPin        A0    // Define Push Button Pin
#define resetPin      A1    // Define Push Button Pin
#define setLEDPin     7     // Define LED Pin
#define resetLedPin   6     // Define LED Pin
#define outputLEDPin  5     // Define LED Pin

MicroBeaut_SR srFunction;   // SR Variable
bool setState;              // Toggle State
bool resetState;            // Toggle State

// Latching Purposes
MicroBeaut_Toggle toggleSet;    // Toggle Variable
MicroBeaut_Toggle toggleReset;  // Toggle Variable

// Serial Plotter Purpose
MicroBeaut_Trigger triggerPlotter;      // Toggle Variable
unsigned long lineNumber;               // Line Number : Max = 9999
const uint16_t plotterPresetTime = 250; // 250 milliseconds

void setup() {
  Serial.begin(115200);                           // Set Baud Rate
  triggerPlotter.setTimeDelay(plotterPresetTime); // Initial Time Delay for Serial Plotter

  pinMode(setPin, INPUT);         // Input Pin Mode
  pinMode(resetPin, INPUT);       // Input Pin Mode
  pinMode(setLEDPin, OUTPUT);     // Output Pin Mode
  pinMode(resetLedPin, OUTPUT);   // Output Pin Mode
  pinMode(outputLEDPin, OUTPUT);  // Output Pin Mode
}

void loop() {
  setState = digitalRead(setPin);     // Read Input State (0 = Release, 1 = Press)
  toggleSet.readInput(setState);         // Toggle Function with Input Parameter
  digitalWrite(setLEDPin, toggleSet.readStatus());  // ON/OFF LED

  resetState = digitalRead(resetPin);   // Read Input State (0 = Release, 1 = Press)
  toggleReset.readInput(resetState);    // Toggle Function with Input Parameter
  digitalWrite(resetLedPin, toggleReset.readStatus());  // ON/OFF LED

  // To Test SR Function
  srFunction.readInput(toggleSet.readStatus(), toggleReset.readStatus()); // SR Function with Set/Reset Parameter
  digitalWrite(outputLEDPin, srFunction.readStatus());         // ON/OFF LED

  // Toggle for Serial Plotter
  if (triggerPlotter.readInput(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;           // Compare / Increase / Reset Line Number
    Serial.println("L" + String(lineNumber)                       // Plotter Line Number
                   + " Set: " + String(toggleSet.readStatus())          // Set State
                   + ", Reset: " + String(toggleReset.readStatus())     // Reset State
                   + ", Output: " + String(srFunction.readStatus()));   // Output State
  }
}