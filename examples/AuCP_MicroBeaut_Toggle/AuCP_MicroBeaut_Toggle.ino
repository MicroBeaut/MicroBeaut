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
  Function: Toggle

  The rising edge of input "toggleInput" toggles Output.
  Input "resetInput" resets the Output (to FALSE).

  Member:
  bool Toggle(bool toggleInput, bool resetInput = false);
  bool readStatus(void);

  Declaration:
  Microbeaut_Toggle variableName

  Parameters:
  Input:
  Input           : Input
  Reset           : Reset

  Return:
  TRUE or FALSE (HIGH/LOW)

  Get Output/Parameters:
  boolVariable = variableName.readStatus();

  Syntax:
  boolVariable = variableName.Toggle(boolInput, boolReset);

*/
//WokWi: https://wokwi.com/arduino/projects/324032370802950738

#include "MicroBeaut.h"

#define inputPin    A0  // Define Push Button Pin
#define resetPin    A1  // Define Push Button Pin
#define outputPin   7   // Define LED Pin

bool inputState;        // Input State
bool resetState;        // Input State
bool outputState;       // Output State

MicroBeaut_Toggle toggleFuncton;  // Toggle Variable

// Printing Purpose
MicroBeaut_Trigger triggerPlotter;    // Toggle Variable
unsigned long lineNumber;             // Line Number : Max = 9999
const uint16_t plotterPresetTime = 10; // 10 milliseconds

void setup() {
  Serial.begin(115200);                           // Set Baud Rate
  triggerPlotter.setTimeDelay(plotterPresetTime); // Initial Time Delay for Printing

  pinMode(inputPin, INPUT);   // Input Pin Mode
  pinMode(resetPin, INPUT);   // Input Pin Mode
  pinMode(outputPin, OUTPUT); // Output Pin Mode
}

void loop() {
  inputState = digitalRead(inputPin); // Read Input State (0 = Release, 1 = Press)
  resetState = digitalRead(resetPin); // Read Input State (0 = Release, 1 = Press)
  outputState = toggleFuncton.readInput(inputState, resetState);  // Toggle Function with Input Parameter
  digitalWrite(outputPin, outputState);    // ON/OFF LED

  // Toggle for Printing
  if (triggerPlotter.readInput(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber)
                   + ", Input: " + String(inputState)     // Input State
                   + ", Reset: " + String(resetState)     // Reset State
                   + ", readStatus: " + String(outputState)); // Output State
  }
}