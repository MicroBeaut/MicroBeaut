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
  Function: Trigger

  The rising edge of input "enableInput" starts a timer of duration "timeDelay".
  When the elapsed time is greater than or equal to "timeDelay",
  the timer restart and output changes from FALSE to TRUE one scan.
  The output does not change if the input "enableInput" is FALSE.

  Member:
  void setTimeDelay(uint16_t timeDelay);
  bool readInput(bool enableInput = true, bool resetInput = false);
  uint16_t getTimeDelay(void);
  uint16_t getElapsedTime(void);

  Declaration:
  Microbeaut_Trigger variableName

  Parameters:
  Input:
  Input           : Input
  Time Delay      : Time Delay in Milliseconds;

  Return:
  TRUE or FALSE (HIGH/LOW)

  Get Output/Parameters:
  boolVariable = variableName.readStatus();
  uint16Variable = variableName.getTimeDelay();    // Return Current Time Trigger
  uint16Variable = variableName.getElapsedTime();  // Return Elapsed Time

  Syntax:
  variableName.setTimeDelay(uint16TimeTrigger);
  boolVariable = variableName.readInput(boolInput, boolReset);
*/
// WokWi: https://wokwi.com/arduino/projects/324014687430640212

#include "MicroBeaut.h"

#define inputPin  A0  // Define Push Button Pin
#define resetPin  A1  // Define Push Button Pin
#define outputPin 7   // Define LED Pin

bool inputState;  // Input State
bool resetState;  // Input State
bool outputState; // Output State

MicroBeaut_Trigger triggerFunction;   // Trigger Variable
const uint16_t timeDelay = 1000;      // Time Delay 1 second

// Serial Plotter Purpose
MicroBeaut_Trigger triggerPlotter;      // Trigger Variable
unsigned long lineNumber;               // Line Number : Max = 9999
const uint16_t plotterPresetTime = 10;  // 10 milliseconds

void setup() {
  Serial.begin(115200);                           // Set Baud Rate
  triggerPlotter.setTimeDelay(plotterPresetTime); // Initial Time Delay for Serial Plotter

  pinMode(inputPin, INPUT);   // Input Pin Mode
  pinMode(resetPin, INPUT);   // Input Pin Mode
  pinMode(outputPin, OUTPUT); // Output Pin Mode
  triggerFunction.setTimeDelay(timeDelay);  // Set Time Delay
}

void loop() {
  inputState = !digitalRead(inputPin);  // Read Input State (0 = Release, 1 = Press)
  resetState = digitalRead(resetPin);   // Read Input State (0 = Release, 1 = Press)
  outputState = triggerFunction.readInput(inputState, resetState);  // Trigger Function with Input Parameter
  digitalWrite(outputPin, outputState);     // ON/OFF LED

  // Trigger for Serial Plotter
  if (triggerPlotter.readInput(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber)
                   + ":Preset Time: " + String(triggerFunction.getTimeDelay())     // Get Time Delay
                   + ", Elapsed Time: " + String(triggerFunction.getElapsedTime()) // Get Elapsed Time
                   + ", Enable: " + String(inputState)         // Enable State
                   + ", Reset: " + String(resetState)          // Reset State
                   + ", Output: " + String(outputState));      // Output State
  }
}