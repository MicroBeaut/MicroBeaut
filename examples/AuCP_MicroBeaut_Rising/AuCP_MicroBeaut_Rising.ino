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
  Function: Rising

  Set the Output on the rising edge of Input.

  Member:
  Microbeaut_Rising(void);
  bool Rising(bool risingInput);

  Declaration:
  Microbeaut_Rising variableName

  Parameters:
  Input:
  RisingInput           : Input

  Return:
  TRUE or FALSE (HIGH/LOW)

  Get Output/Parameters:
  boolVariable = variableName.Output();

  Syntax:
  boolVariable = variableName.Rising(boolInput);

*/
// WokWi: https://wokwi.com/arduino/projects/324033361796399700

#include "MicroBeaut.h"

#define inputPin   2  // Define Push Button Pin
#define outputPin  3  // Define LED Pin

bool inputState;  // Input State
bool outputState; // Output State

MicroBeaut_Rising reInput;  // Rising Edge Variable
int counterValue;           // Count-Up Variable

// Serial Plotter Purpose
MicroBeaut_Trigger triggerPlotter;  // Trigger Variable
unsigned long lineNumber;           // Line Number : Max = 9999
const float plotterPresetTime = 0.100;  // 100 milliseconds

const float timeDelay = 1.0;  // Time Delay 1 second

void setup() {
  Serial.begin(115200);                           // Set Baud Rate
  triggerPlotter.SetTimeDelay(plotterPresetTime); // Initial Time Delay for Serial Plotter

  pinMode(inputPin, INPUT);   // Input Pin Mode
  pinMode(outputPin, OUTPUT); // Output Pin Mode
}

void loop() {
  inputState = digitalRead(inputPin);       // Read Input State (0 = Release, 1 = Press)
  outputState = reInput.Rising(inputState); // Rising Edge Function with Input Parameter

  // Counter by Rising Edge Input
  if (outputState) {
    counterValue = counterValue < 15 ? counterValue + 1 : 0;
  }
  digitalWrite(outputPin, outputState);            // ON/OFF LED

  // Trigger for Serial Plotter
  if (triggerPlotter.Trigger(true) | outputState) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber)
                   + ", Input: " + String(inputState)              // Input State
                   + ", Output: " + String(outputState)            // Output State
                   + " :Counter Number: " + String(counterValue)); // Counter Value
  }
}