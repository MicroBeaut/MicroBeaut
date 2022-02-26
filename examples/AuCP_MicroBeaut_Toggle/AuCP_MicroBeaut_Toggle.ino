/*
  -- ========================================================
  -- Subject: Applied Microcontroller Programming (AuCP)
  -- Purpose: Applied PLC Function to MCU.
  -- Author:  Montree Hamarn
  -- Email:   montree.hamarn@gmail.com
  -- GitHub:  https://github.com/MicroBeaut
  -- YouTube: What Did You Learn Today
  --          https://www.youtube.com/playlist?list=PLFf3xtcn9d47akU0G3bf2BXiMebCzrvMm
  -- ========================================================
*/
/*
  -- ===========================================================================
  Function: Toggle

  The rising edge of input "Input" toggles Output.
  Input "Reset" resets the Output (to FALSE).

  Member:
  bool Toggle(bool Input);
  bool Toggle(bool Input, bool Reset);

  Declaration:
  Microbeaut_Toggle variableName

  Parameters:
  Input:
  Input           : Input
  Reset           : Reset

  Return:
  TRUE or FALSE (HIGH/LOW)

  Get Output/Parameters:
  boolVariable = variableName.Output();
	
  Syntax:
  Option 1:
  boolVariable = variableName.Toggle(boolInput);

  Option 2:
  boolVariable = variableName.Toggle(boolInput, boolReset);
*/
//WokWi: https://wokwi.com/arduino/projects/324032370802950738

#include "MicroBeaut.h"

#define btInputPin    A0        // Define Push Button Pin
#define btResetPin    A1        // Define Push Button Pin
#define ledOutputPin  7         // Define LED Pin

MicroBeaut_Toggle tgOutput;     // Toggle Variable
bool inputState;                // Input State
bool resetState;                // Input State
bool outputState;               // Output State


// Printing Purpose
MicroBeaut_Trigger trigDisplay;     // Toggle Variable
unsigned long lineNumber;           // Line Number : Max = 9999
const float printPresetTime = 0.01; // 10 milliseconds


// TYPE YOUR OPTION (OPTION1-2)
//************************************************************
#define OPTION1                    // Select Option to Compile
//************************************************************

const float timeDelay = 1.0;  // Time Delay 1 second

void setup() {
  Serial.begin(115200);                       // Set Baud Rate
  trigDisplay.SetTimeDelay(printPresetTime);  // Initial Time Delay for Printing

  pinMode(btInputPin, INPUT);                 // Input Pin Mode
  pinMode(btResetPin, INPUT);                 // Input Pin Mode
  pinMode(ledOutputPin, OUTPUT);              // Output Pin Mode
}

void loop() {

  inputState = digitalRead(btInputPin); // Read Input State (0 = Release, 1 = Press)
  resetState = digitalRead(btResetPin); // Read Input State (0 = Release, 1 = Press)

  // Toggle OPTION 1: Toggle Function with Input
#if defined (OPTION1)
  outputState = tgOutput.Toggle(inputState);  // Toggle Function with Input Parameter
  digitalWrite(ledOutputPin, outputState);    // ON/OFF LED

  // Toggle OPTION 2: Toggle Function with Input and Reset
#elif defined (OPTION2)
  outputState = tgOutput.Toggle(inputState, resetState);  // Toggle Function with Input Parameter
  digitalWrite(ledOutputPin, outputState);                // ON/OFF LED
#endif

  // Toggle for Printing
  if (trigDisplay.Trigger(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber)
                   + ", Input: " + String(inputState)     // Input State
                   + ", Reset: " + String(resetState)     // Reset State
                   + ", Output: " + String(outputState)); // Output State
  }
}