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
  Function:  TimeSchedule
  Purpose:   Schedule execution at specified time intervals.

  Function TimeScedule schedules the execution of certain routines at
  desired time intervals. Output is TRUE when the specified "period."
  of time has passed, holding TRUE for one scan; otherwise, output Output is FALSE.
  By testing the output Output, you can cause sections of the control program
  to be executed periodically.

  Member:
  void Config(float timeSchedule, MicroBeaut_CallBackFunction functionName);
  bool Run(bool enableInput = true);
  float Actual(void);
  bool Output(void);

  Declaration:
  Microbeaut_TimeSchedule variableName

  Parameters:
  Input:
  enableInput     : Enable Time Schedule Function
  TimeSchedule    : Time Intervals in Second
  FunctionName    : CallBack Function
  Return:
  TRUE or FALSE (HIGH/LOW)

  Get Output/Parameters:
  boolVariable = variableName.Output();
  floatVariable = variableName.Actual();

  Syntax:
  variableName.Config(timeSchedule, functionName);
  boolVariable = Run(enableInput);

*/
// WokWi: https://wokwi.com/arduino/projects/324491194348339795

#include "MicroBeaut.h"

#define inputPin    A0  // Define Push Button Pin
#define outputPin   7   // Define LED Pin

bool inputState;        // Input State
bool outputState;       // Output State

MicroBeaut_TimeSchedule timeScheduleFunction; // Time Schedule Function
const float timeInterval = 0.5;       // Time Delay 0.5 second

// Serial Plotter Purpose
MicroBeaut_Trigger triggerPlotter;    // Trigger Variable
unsigned long lineNumber;             // Line Number : Max = 9999
const float plotterPresetTime = 0.01; // 10 milliseconds

void setup() {
  Serial.begin(115200);                           // Set Baud Rate
  triggerPlotter.SetTimeDelay(plotterPresetTime); // Initial Time Delay for Serial Plotter

  pinMode(inputPin, INPUT);   // Input Pin Mode
  pinMode(outputPin, OUTPUT); // Output Pin Mode
  timeScheduleFunction.Config(timeInterval, ToggleStateLED);  // Time Schedule Function with Input Parameter
}

void loop() {
  inputState = !digitalRead(inputPin);  // Read Input State (0 = Release, 1 = Press)
  timeScheduleFunction.Run(inputState);         // Time Schedule Function with Enable Parameter
  digitalWrite(outputPin, outputState); // ON/OFF LED


  // Time Schedule for Serial Plotter
  if (triggerPlotter.Trigger(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber)
                   + ", Enable: " + String(inputState)    // Input State
                   + ", Output: " + String(outputState)   // Output State
                   + ", Actual Time: " + String(timeScheduleFunction.Actual(), 6));
  }
}

void ToggleStateLED()
{
  outputState = !outputState;
}