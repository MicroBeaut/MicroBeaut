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
  Function: TimePulse

  Generate a pulse of duration "TimeDelay" starting on the rising edge of the input

  Member:
  void SetTimeDelay(float timeDelay);
  bool TimePulse(bool pulseInput);
  float GetTimeDelay(void);
  float GetElapsedTime(void);

  Declaration:
  Microbeaut_TimePulse variableName

  Parameters:
  Input:
  Input           : Input
  Time Delay      : Time Delay in Second;

  Return:
  TRUE or FALSE (HIGH/LOW)

  Get Output/Parameters:
  boolVariable = variableName.Output();
  floatVariable = variableName.GetTimeDelay();    // Return Current Time Time Pulse
  floatVariable = variableName.GetElapsedTime();  // Return Elapsed Time

  Syntax:
  variableName.SetTimeDelay(floatTimePulse);
  boolVariable = variableName.TimePulse(boolInput);
*/
// WokWi: https://wokwi.com/arduino/projects/324006931497747028

#include "MicroBeaut.h"

#define inputPin   2               // Define Push Button Pin
#define outputPin  3               // Define LED Pin

bool inputState;  // Input State
bool outputState; // Output State
MicroBeaut_TimePulse timepulseFunction; // Time Pulse Variable
const float timeDelay = 1.0;            // Time Delay 1 second

// Serial Plotter Purpose
MicroBeaut_Trigger triggerPlotter;  // Trigger Variable
unsigned long lineNumber;           // Line Number : Max = 9999
const float plotterPresetTime = 0.01;  // 10 milliseconds



void setup() {
  Serial.begin(115200);                           // Set Baud Rate
  triggerPlotter.SetTimeDelay(plotterPresetTime);   // Initial Time Delay for Serial Plotter

  pinMode(inputPin, INPUT);              // Input Pin Mode
  pinMode(outputPin, OUTPUT);            // Output Pin Mode
  timepulseFunction.SetTimeDelay(timeDelay);  // Set Time Delay
}

void loop() {
  inputState = digitalRead(inputPin);    // Read Input State (0 = Release, 1 = Press)
  outputState = timepulseFunction.TimePulse(inputState);   // Time Pulse Function with Input Parameter
  digitalWrite(outputPin, outputState); // ON/OFF LED


  // Trigger for Serial Plotter
  if (triggerPlotter.Trigger(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber)
                   + ":Preset Time: " + String(timepulseFunction.GetTimeDelay(), 6)     // Get Time Delay
                   + ", Elapsed Time: " + String(timepulseFunction.GetElapsedTime(), 6) // Get Elapsed Time
                   + ", Input: " + String(inputState)           // Input State
                   + ", Output: " + String(outputState));      // Output State
  }
}