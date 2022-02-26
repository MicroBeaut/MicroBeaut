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
  Function:  TimeSchedule
  Purpose:   Schedule execution at specified time intervals.

  Function TimeScedule schedules the execution of certain routines at
  desired time intervals. Output is TRUE when the specified "period."
  of time has passed, holding TRUE for one scan; otherwise, output Output is FALSE.
  By testing the output Output, you can cause sections of the control program
  to be executed periodically.

  Member:
  void Setup(float TimeSchedule, MicroBeaut_CallBackFunction FunctionName);
  bool Run(bool enableInput);
  bool Run(bool enableInput, float msTimeSchedule, MicroBeaut_CallBackFunction FunctionName);
  float Actual(void);

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
  Option 1:
  variableName.Setup(timeSchedule, functionName);
  boolVariable = Run(enableInput);

  Option 2:
  boolVariable = Run(enableInput, timeSchedule, functionName);
*/
// WokWi: https://wokwi.com/arduino/projects/324491194348339795

#include "MicroBeaut.h"

#define btInputPin    A0        // Define Push Button Pin
#define ledOutputPin  7         // Define LED Pin

MicroBeaut_TimeSchedule timeSchedule; // Time Schedule Function
bool disableState;                    // Input State
bool outputState;                     // Output State


// Serial Plotter Purpose
MicroBeaut_Trigger trigDisplay;     // Trigger Variable
unsigned long lineNumber;           // Line Number : Max = 9999
const float printPresetTime = 0.01; // 10 milliseconds


// TYPE YOUR OPTION (OPTION1-2)
//************************************************************
#define OPTION1                    // Select Option to Compile
//************************************************************

const float timeInterval = 0.5; // Time Delay 0.5 second

void setup() {
  Serial.begin(115200);                       // Set Baud Rate
  trigDisplay.SetTimeDelay(printPresetTime);  // Initial Time Delay for Serial Plotter


  pinMode(btInputPin, INPUT);     // Input Pin Mode
  pinMode(ledOutputPin, OUTPUT);  // Output Pin Mode

  // Time Schedule OPTION 1: Time Schedule Function with Enable Input and CallBack Function
#if defined (OPTION1)
  timeSchedule.Setup(timeInterval, ToggleStateLED);  // Time Schedule Function with Input Parameter
#endif
}

void loop() {

  disableState = !digitalRead(btInputPin);  // Read Input State (0 = Release, 1 = Press)

  // Time Schedule OPTION 1: Time Schedule Function with Enable Input
#if defined (OPTION1)
  timeSchedule.Run(disableState);           // Time Schedule Function with Enable Parameter


  // Time Schedule OPTION 2: Time Schedule Function with All Parameters
#elif defined (OPTION2)
  timeSchedule.Run(disableState, timeInterval, ToggleStateLED);  // Time Schedule Function with All Parameters
#endif

  digitalWrite(ledOutputPin, outputState); // ON/OFF LED

  // Time Schedule for Serial Plotter
  if (trigDisplay.Trigger(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber)
                   + ", Enable: " + String(disableState)      // Input State
                   + ", Output: " + String(outputState)       // Output State
                   + ", Actual Time: " + String(timeSchedule.Actual(), 6));
  }
}

void ToggleStateLED()
{
  outputState = !outputState;
}
