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
  Function: Trigger

  The rising edge of input "Input" starts a timer of duration "TimeDelay".
  When the elapsed time is greater than or equal to "TimeDelay",
  the timer restart and output changes from FALSE to TRUE one scan.
  The output does not change if the input "Input" is FALSE.

  Member:
  Microbeaut_Trigger(void);
  void SetTimeDelay(float TimeDelay);
  bool Trigger(bool Input);
  bool Trigger(bool Input, float TimeDelay);
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


  Syntax:
  Option 1:
      variableName.SetTimeDelay(floatTimeTrigger);
      boolVariable = variableName.Trigger(boolInput);

  Option 2:
    variableName.SetTimeDelay(floatTimeTrigger);
    boolVariable = variableName.Trigger(boolInput, boolReset);

  Option 3:
  boolVariable = variableName.Trigger(boolInput, boolReset, floatTimeTrigger);


  Get Parameters:
    floatVariable = variableName.GetTimeDelay();    // Return Current Time Trigger
    floatVariable = variableName.GetElapsedTime();  // Return Elapsed Time
*/
// https://wokwi.com/arduino/projects/324014687430640212

#include "MicroBeaut.h"

#define btEnablePin   A0               // Define Push Button Pin
#define btResetPin    A1               // Define Push Button Pin
#define ledOutputPin  7               // Define LED Pin

MicroBeaut_Trigger tgOutput;    // Trigger Variable
bool enableState;                // Input State
bool resetState;                // Input State
bool outputState;               // Output State


// Serial Plotter Purpose
MicroBeaut_Trigger triggerDisplay;  // Trigger Variable
unsigned long lineNumber;           // Line Number : Max = 9999
const float printPresetTime = 0.01;  // 10 milliseconds


// TYPE YOUR OPTION (OPTION1-3)
//************************************************************
#define OPTION1                    // Select Option to Compile
//************************************************************

const float timeDelay = 1.0;          // Time Delay 1 second

void setup() {
  Serial.begin(115200);                           // Set Baud Rate
  triggerDisplay.SetTimeDelay(printPresetTime);   // Initial Time Delay for Serial Plotter

  pinMode(btEnablePin, INPUT);             // Input Pin Mode
  pinMode(btResetPin, INPUT);              // Input Pin Mode
  pinMode(ledOutputPin, OUTPUT);           // Output Pin Mode
}

void loop() {

  enableState = digitalRead(btEnablePin);  // Read Input State (0 = Release, 1 = Press)
  resetState = digitalRead(btResetPin);    // Read Input State (0 = Release, 1 = Press)

  // Trigger OPTION 1
  // 1. Setup Time Delay for Trigger
  // 2. Trigger Function with Input
#if defined (OPTION1)
  tgOutput.SetTimeDelay(timeDelay);             // Set Time Delay
  outputState = tgOutput.Trigger(enableState);  // Trigger Function with Input Parameter
  digitalWrite(ledOutputPin, outputState);      // ON/OFF LED

  // Trigger OPTION 2
  // 1. Setup Time Delay for Trigger
  // 2. Trigger Function with Input and Reset
#elif defined (OPTION2)
  tgOutput.SetTimeDelay(timeDelay);                         // Set Time Delay
  outputState = tgOutput.Trigger(enableState, resetState);  // Trigger Function with Input Parameter
  digitalWrite(ledOutputPin, outputState);                  // ON / OFF LED

  // Trigger OPTION 3: Trigger Function with Input
#elif defined (OPTION3)
  outputState = tgOutput.Trigger(!enableState, resetState, timeDelay);  // Trigger Function with Input and Reset Parameter
  digitalWrite(ledOutputPin, outputState);                              // ON/OFF LED
#endif

  // Trigger for Serial Plotter
  if (triggerDisplay.Trigger(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber)
                   + ":Preset Time: " + String(tgOutput.GetTimeDelay(), 6)     // Get Time Delay
                   + ", Elapsed Time: " + String(tgOutput.GetElapsedTime(), 6) // Get Elapsed Time
                   + ", Input: " + String(enableState)         // Input State
                   + ", Reset: " + String(resetState)          // Reset State
                   + ", Output: " + String(outputState));      // Output State
  }
}