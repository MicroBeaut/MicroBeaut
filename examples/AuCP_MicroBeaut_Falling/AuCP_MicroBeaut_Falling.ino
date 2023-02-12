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
  Function: Falling

  Set the Output on the falling edge of Input.

  Member:
  bool readInput(bool fallingInput);

  Declaration:
  Microbeaut_Falling variableName

  Parameters:
  Input:
  FallingInput         : Input

  Return:
  TRUE or FALSE (HIGH/LOW)

  Get Output/Parameters:
  boolVariable = variableName.readStatus(); // Return Current Output State


  Syntax:
  boolVariable = variableName.readInput(boolInput);

*/
// WokWi: https://wokwi.com/arduino/projects/324035086096794195

#include "MicroBeaut.h"

#define inputPin   2  // Define Push Button Pin
#define outputPin  3  // Define LED Pin

bool inputState;                // Input State
bool outputState;               // Output State

MicroBeaut_Falling fallingFunction; // Falling Edge Variable
int counterValue;                   // Count-Up Variable

// Serial Plotter Purpose
MicroBeaut_Trigger triggerPlotter;  // Trigger Variable
unsigned long lineNumber;           // Line Number : Max = 9999
const uint16_t plotterPresetTime = 100;  // 100 milliseconds

void setup() {
  Serial.begin(115200);                           // Set Baud Rate
  triggerPlotter.setTimeDelay(plotterPresetTime); // Initial Time Delay for Serial Plotter

  pinMode(inputPin, INPUT);              // Input Pin Mode
  pinMode(outputPin, OUTPUT);            // OutputPin Mode
}

void loop() {
  inputState = digitalRead(inputPin);              // Read Input State (0 = Release, 1 = Press)
  outputState = fallingFunction.readInput(inputState);    // Falling Edge Function with Input Parameter

  // Counter by Falling Edge Input
  if (outputState) {
    counterValue = counterValue < 15 ? counterValue + 1 : 0;
  }
  digitalWrite(outputPin, outputState);            // ON/OFF LED

  // readInput for Serial Plotter
  if (triggerPlotter.readInput(true) | outputState) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber)
                   + ", Input: " + String(inputState)              // Input State
                   + ", readStatus: " + String(outputState)            // Output State                   
                   + " :Counter Number: " + String(counterValue)); // Counter Value
  }
}