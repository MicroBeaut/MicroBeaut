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
  Function: TimerOn

  The rising edge of input "timerOnInput" starts a timer of duration "TimeDelay".
  When the elapsed time is greater than or equal to "TimeDelay",
  the timer stops, and output changes from FALSE to TRUE.
  The next falling edge of the input "timerOnInput" initializes the timer.

  Member:
  void SetTimeDelay(float timeDelay);
  bool TimerOn(bool timerOnInput);
  float GetTimeDelay(void);
  float GetElapsedTime(void);

  Declaration:
  MicroBeaut_TimerOn variableName

  Parameters:
  Input:
  Input           : Input
  Time Delay      : Time Delay in Second;

  Return:
  TRUE or FALSE (HIGH/LOW)

  Get Output/Parameters:
  boolVariable = variableName.Output();
  floatVariable = variableName.GetTimeDelay();    // Return Current Time Timer On
  floatVariable = variableName.GetElapsedTime();  // Return Elapsed Time

  Syntax:
  variableName.SetTimeDelay(floatTimeDelayOn);
  boolVariable = variableName.TimerOn(boolInput);

*/
// WokWi: https://wokwi.com/arduino/projects/324001504402866770

#include "MicroBeaut.h"

#define inputPin   2  // Define Push Button Pin
#define outputPin  3  // Define LED Pin

bool inputState;      // Input State
bool outputState;     // Output State

MicroBeaut_TimerOn tonOutput; // Timer On Variable
const float timeDelay = 1.0;  // Time Delay 1 second

// Serial Plotter Purpose
MicroBeaut_Trigger triggerPlotter;      // Trigger Variable
unsigned long lineNumber;               // Line Number : Max = 9999
const float plotterPresetTime = 0.01;  // 10 milliseconds

void setup() {
  Serial.begin(115200);                             // Set Baud Rate
  triggerPlotter.SetTimeDelay(plotterPresetTime);   // Initial Time Delay for Serial Plotter

  pinMode(inputPin, INPUT);     // Input Pin Mode
  pinMode(outputPin, OUTPUT);   // Output Pin Mode
  tonOutput.SetTimeDelay(timeDelay);  // Set Time Delay
}

void loop() {
  inputState = digitalRead(inputPin);           // Read Input State (0 = Release, 1 = Press)
  outputState = tonOutput.TimerOn(inputState);  // Timer On Function with Input Parameter
  digitalWrite(outputPin, outputState);         // ON/OFF LED


  // Trigger for Serial Plotter
  if (triggerPlotter.Trigger(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber)
                   + ":Preset Time: " + String(tonOutput.GetTimeDelay(), 6)     // Get Time Delay
                   + ", Elapsed Time: " + String(tonOutput.GetElapsedTime(), 6) // Get Elapsed Time
                   + ", Input: " + String(inputState)            // Input State
                   + ", Output: " + String(outputState));        // Output State
  }
}