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
  Function: TimePulse

  Generate a pulse of duration "TimeDelay" starting on the rising edge of the input

  Member:
  Microbeaut_TimePulse(void);
  void SetTimeDelay(float TimeDelay);
  bool TimePulse(bool Input);
  bool TimePulse(bool Input, float TimeDelay);
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


  Syntax:
  Option 1:
      variableName.SetTimeDelay(floatTimePulse);
      boolVariable = variableName.TimePulse(boolInput);

  Option 2:
    boolVariable = variableName.TimePulse(boolInput, floatTimePulse);


  Get Parameters:
    floatVariable = variableName.GetTimeDelay();    // Return Current Time Time Pulse
    floatVariable = variableName.GetElapsedTime();  // Return Elapsed Time
*/
// https://wokwi.com/arduino/projects/324006931497747028

#include "MicroBeaut.h"

#define swPin   2               // Define Push Button Pin
#define ledPin  3               // Degine LED Pin

MicroBeaut_TimePulse tpOutput;  // Time Pulse Variable
bool inputState;                // Input State
bool outputState;               // Output State


// Printing Purpose
MicroBeaut_Trigger triggerDisplay;  // Trigger Variable
unsigned long lineNumber;           // Line Number : Max = 9999
const float printPresetTime = 0.01;  // 10 milliseconds


// TYPE YOUR OPTION (OPTION1-2)
//************************************************************
#define OPTION1                     // Select Option to Compile
//************************************************************

const float timeDelay = 1.0;          // Time Delay 1 second

void setup() {
  Serial.begin(115200);                           // Set Buad Rate
  triggerDisplay.SetTimeDelay(printPresetTime);   // Initial Time Delay for Printing

  pinMode(swPin, INPUT);              // Input Pin Mode
  pinMode(ledPin, OUTPUT);            // Output Pin Mode
}

void loop() {

  inputState = digitalRead(swPin);    // Read Input State (0 = Release, 1 = Press)

  // Time Pulse OPTION 1
  // 1. Setup Time Delay for Time Pulse
  // 2. Time Pulse Function wiht Input
#if defined (OPTION1)
  tpOutput.SetTimeDelay(timeDelay);                  // Set Time Delay
  outputState = tpOutput.TimePulse(inputState);           // Time Pulse Function with Input Parameter
  digitalWrite(ledPin, outputState);                     // ON/OFF LED

  // Time Pulse OPTION 2: Time Pulse Function wiht Input
#elif defined (OPTION2)
  outputState = tpOutput.TimePulse(inputState, timeDelay);  // Time Pulse Function with Input Parameter
  digitalWrite(ledPin, outputState);                       // ON/OFF LED
#endif

  // Trigger for Printing
  if (triggerDisplay.Trigger(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber)
                   + ":Preset Time: " + String(tpOutput.GetTimeDelay(), 6)     // Get Time Delay
                   + ", Elapsed Time: " + String(tpOutput.GetElapsedTime(), 6) // Get Elapsed Time
                   + ", Input: " + String(inputState)           // Input State
                   + ", Output: " + String(outputState));      // Output State
  }
}