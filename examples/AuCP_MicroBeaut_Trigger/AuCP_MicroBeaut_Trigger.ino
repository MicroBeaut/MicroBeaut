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
  void SetTimeDelay(float timeDelay);
  bool Trigger(bool enableInput = true, bool resetInput = false);
  float GetTimeDelay(void);
  float GetElapsedTime(void);

  Declaration:
  Microbeaut_Trigger variableName

  Parameters:
  Input:
  Input           : Input
  Time Delay      : Time Delay in Second;

  Return:
  TRUE or FALSE (HIGH/LOW)

  Get Output/Parameters:
  boolVariable = variableName.Output();
  floatVariable = variableName.GetTimeDelay();    // Return Current Time Trigger
  floatVariable = variableName.GetElapsedTime();  // Return Elapsed Time

  Syntax:
  variableName.SetTimeDelay(floatTimeTrigger);
  boolVariable = variableName.Trigger(boolInput, boolReset);
*/
// WokWi: https://wokwi.com/arduino/projects/324014687430640212

#include "MicroBeaut.h"

#define inputPin  A0  // Define Push Button Pin
#define resetPin  A1  // Define Push Button Pin
#define outputPin 7   // Define LED Pin

bool inputState;  // Input State
bool resetState;  // Input State
bool outputState; // Output State

MicroBeaut_Trigger triggerFunction;  // Trigger Variable
const float timeDelay = 1.0;          // Time Delay 1 second

// Serial Plotter Purpose
MicroBeaut_Trigger triggerPlotter;  // Trigger Variable
unsigned long lineNumber;           // Line Number : Max = 9999
const float plotterPresetTime = 0.01; // 10 milliseconds



void setup() {
  Serial.begin(115200);                         // Set Baud Rate
  triggerPlotter.SetTimeDelay(plotterPresetTime); // Initial Time Delay for Serial Plotter

  pinMode(inputPin, INPUT);   // Input Pin Mode
  pinMode(resetPin, INPUT);   // Input Pin Mode
  pinMode(outputPin, OUTPUT); // Output Pin Mode
  triggerFunction.SetTimeDelay(timeDelay);  // Set Time Delay
}

void loop() {

  inputState = !digitalRead(inputPin); // Read Input State (0 = Release, 1 = Press)
  resetState = digitalRead(resetPin); // Read Input State (0 = Release, 1 = Press)
  outputState = triggerFunction.Trigger(inputState, resetState);  // Trigger Function with Input Parameter
  digitalWrite(outputPin, outputState);     // ON/OFF LED

  // Trigger for Serial Plotter
  if (triggerPlotter.Trigger(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber)
                   + ":Preset Time: " + String(triggerFunction.GetTimeDelay(), 6)     // Get Time Delay
                   + ", Elapsed Time: " + String(triggerFunction.GetElapsedTime(), 6) // Get Elapsed Time
                   + ", Enable: " + String(inputState)         // Enable State
                   + ", Reset: " + String(resetState)          // Reset State
                   + ", Output: " + String(outputState));      // Output State
  }
}