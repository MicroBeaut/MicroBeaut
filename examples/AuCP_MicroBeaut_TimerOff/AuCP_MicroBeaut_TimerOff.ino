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
  Function: TimerOff

  The falling edge of input "timerOffInput" starts a timer of duration "TimeDelay".
  When the elapsed time is greater than or equal to "TimeDelay",
  the timer stops, and output changes from TRUE to FALSE.
  If the input "timerOffInput" is TRUE, then TimerOff sets the output to TRUE
  and the elapsed time to zero.

  Member:
  void SetTimeDelay(float timeDelay);
  bool TimerOff(bool timerOffInput);
  bool Output(void);
  float GetTimeDelay(void);
  float GetElapsedTime(void);

  Declaration:
  MicroBeaut_TimerOff variableName

  Parameters:
  Input:
  Input           : Input
  Time Delay      : Time Delay in Second;

  Return:
  TRUE or FALSE (HIGH/LOW)

  Get Output/Parameters:
  boolVariable = variableName.Output();
  floatVariable = variableName.GetTimeDelay();    // Return Current Time Timer Off
  floatVariable = variableName.GetElapsedTime();  // Return Elapsed Time

  Syntax:
  variableName.SetTimeDelay(floatTimeDelayOn);
  boolVariable = variableName.TimerOff(boolInput);

*/
// WokWi: https://wokwi.com/arduino/projects/324004619609965140

#include "MicroBeaut.h"

#define inputPin   2  // Define Push Button Pin
#define outputPin  3  // Degine LED Pin

bool inputState;      // Input State
bool outputState;     // Output State

MicroBeaut_TimerOff tofFunction;  // Timer Off Variable
const float timeDelay = 1.0;      // Time Delay 1 second

// Serial Plotter Purpose
MicroBeaut_Trigger triggerPlotter;  // Trigger Variable
unsigned long lineNumber;           // Line Number : Max = 9999
const float plotterPresetTime = 0.01; // 10 milliseconds

void setup() {
  Serial.begin(115200);                           // Set Baud Rate
  triggerPlotter.SetTimeDelay(plotterPresetTime);   // Initial Time Delay for Serial Plotter

  pinMode(inputPin, INPUT_PULLUP);    // Input Pin Mode
  pinMode(outputPin, OUTPUT);         // Output Pin Mode
  tofFunction.SetTimeDelay(timeDelay);  // Set Time Delay
}

void loop() {
  inputState = digitalRead(inputPin);    // Read Input State (0 = Press, 1 = Release)
  outputState = tofFunction.TimerOff(inputState); // Timer Off Function with Input Parameter
  digitalWrite(outputPin, outputState);         // ON/OFF LED


  // Trigger for Serial Plotter
  if (triggerPlotter.Trigger(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber)
                   + ":Preset Time: " + String(tofFunction.GetTimeDelay(), 6)     // Get Time Delay
                   + ", Elapsed Time: " + String(tofFunction.GetElapsedTime(), 6) // Get Elapsed Time
                   + ", Input: " + String(inputState)                             // Input State
                   + ", Output: " + String(outputState));                         // Output State
  }
}