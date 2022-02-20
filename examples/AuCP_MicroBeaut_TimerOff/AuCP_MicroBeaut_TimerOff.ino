/*
  -- ========================================================
  -- Subject: Applied Microcontroller Programming (AuCP)
  -- Purpose: Applied PLC Function to MCU.
  -- Author:  Montree Hamarn
  -- GitHub:  https://github.com/MicroBeaut
  -- YouTube: What Did You Learn Today
  --          https://www.youtube.com/playlist?list=PLFf3xtcn9d47akU0G3bf2BXiMebCzrvMm
  -- ========================================================
*/
/*
  -- ===========================================================================
  Function: TimerOff

  The falling edge of input "Input" starts a timer of duration "TimeDelay".
  When the elapsed time is greater than or equal to "TimeDelay",
  the timer stops, and output changes from TRUE to FALSE.
  If the input "Input" is TRUE, then TimerOff sets the output to TRUE
  and the elapsed time to zero.

  Member:
  MicroBeaut_TimerOff(void);
  void SetTimeDelay(float TimeDelay);
  bool TimerOff(bool Input);
  bool TimerOff(bool Input, float TimeDelay);
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


  Syntax:
  Option 1:
      variableName.SetTimeDelay(floatTimeDelayOn);
      boolVariable = variableName.TimerOff(boolInput);

  Option 2:
    boolVariable = variableName.TimerOff(boolInput, floatTimeDelayOn);


  Get Parameters:
    floatVariable = variableName.GetTimeDelay();    // Return Current Time Timer Off
    floatVariable = variableName.GetElapsedTime();  // Return Elapsed Time
*/
// https://wokwi.com/arduino/projects/324004619609965140

#include "MicroBeaut.h"

#define swPin   2               // Define Push Button Pin
#define ledPin  3               // Degine LED Pin

MicroBeaut_TimerOff tofOutput;  // Timer Off Variable
bool inputState;                // Input State
bool outputState;               // Output State


// Printing Purpose
MicroBeaut_Trigger triggerDisplay;  // Trigger Variable
unsigned long lineNumber;           // Line Number : Max = 9999
const float printPresetTime = 0.01; // 10 milliseconds


// TYPE YOUR OPTION (OPTION1-2)
//************************************************************
#define OPTION1                     // Select Option to Compile
//************************************************************

const float timeDelay = 1.0;          // Time Delay 1 second

void setup() {
  Serial.begin(115200);                           // Set Buad Rate
  triggerDisplay.SetTimeDelay(printPresetTime);   // Initial Time Delay for Printing

  pinMode(swPin, INPUT_PULLUP);       // Input Pin Mode
  pinMode(ledPin, OUTPUT);            // Output Pin Mode
}

void loop() {

  inputState = digitalRead(swPin);    // Read Input State (0 = Press, 1 = Release)

  // Timer Off OPTION 1
  // 1. Setup Time Delay for Timer Off
  // 2. Timer Off Function wiht Input
#if defined (OPTION1)
  tofOutput.SetTimeDelay(timeDelay);                  // Set Time Delay
  outputState = tofOutput.TimerOff(inputState);           // Timer Off Function with Input Parameter
  digitalWrite(ledPin, outputState);                     // ON/OFF LED

  // Timer Off OPTION 2: Timer Off Function wiht Input
#elif defined (OPTION2)
  outputState = tofOutput.TimerOff(inputState, timeDelay);  // Timer Off Function with Input Parameter
  digitalWrite(ledPin, outputState);                       // ON/OFF LED
#endif

  // Trigger for Printing
  if (triggerDisplay.Trigger(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber)
                   + ":Preset Time: " + String(tofOutput.GetTimeDelay(), 6)     // Get Time Delay
                   + ", Elapsed Time: " + String(tofOutput.GetElapsedTime(), 6) // Get Elapsed Time
                   + ", Input: " + String(inputState)                          // Input State
                   + ", Output: " + String(outputState));                         // Output State
  }
}