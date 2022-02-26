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
  Function: TimerOn

  The rising edge of input "Input" starts a timer of duration "TimeDelay".
  When the elapsed time is greater than or equal to "TimeDelay",
  the timer stops, and output changes from FALSE to TRUE.
  The next falling edge of the input "Input" initializes the timer.

  Member:
  MicroBeaut_TimerOn(void);
  void SetTimeDelay(float TimeDelay);
  bool TimerOn(bool Input);
  bool TimerOn(bool Input, float TimeDelay);
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
  Option 1:
  variableName.SetTimeDelay(floatTimeDelayOn);
  boolVariable = variableName.TimerOn(boolInput);

  Option 2:
  boolVariable = variableName.TimerOn(boolInput, floatTimeDelayOn);
*/
// WokWi: https://wokwi.com/arduino/projects/324001504402866770

#include "MicroBeaut.h"

#define swPin   2               // Define Push Button Pin
#define ledPin  3               // Define LED Pin

MicroBeaut_TimerOn tonOutput;   // Timer On Variable
bool inputState;                // Input State
bool outputState;               // Output State


// Serial Plotter Purpose
MicroBeaut_Trigger triggerDisplay;  // Trigger Variable
unsigned long lineNumber;           // Line Number : Max = 9999
const float printPresetTime = 0.01;  // 10 milliseconds


// TYPE YOUR OPTION (OPTION1-2)
//************************************************************
#define OPTION1                   // Select Option to Compile
//************************************************************

const float timeDelay = 1.0;          // Time Delay 1 second

void setup() {
  Serial.begin(115200);                           // Set Baud Rate
  triggerDisplay.SetTimeDelay(printPresetTime);   // Initial Time Delay for Serial Plotter

  pinMode(swPin, INPUT);              // Input Pin Mode
  pinMode(ledPin, OUTPUT);            // Output Pin Mode
}

void loop() {

  inputState = digitalRead(swPin);    // Read Input State (0 = Release, 1 = Press)

  // Timer On OPTION 1
  // 1. Setup Time Delay for Timer On
  // 2. Timer On Function with Input
#if defined (OPTION1)
  tonOutput.SetTimeDelay(timeDelay);            // Set Time Delay
  outputState = tonOutput.TimerOn(inputState);  // Timer On Function with Input Parameter
  digitalWrite(ledPin, outputState);            // ON/OFF LED

  // Timer On OPTION 2: Timer On Function with Input
#elif defined (OPTION2)
  outputState = tonOutput.TimerOn(inputState, timeDelay);  // Timer On Function with Input Parameter
  digitalWrite(ledPin, outputState);                       // ON/OFF LED
#endif

  // Trigger for Serial Plotter
  if (triggerDisplay.Trigger(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber)
                   + ":Preset Time: " + String(tonOutput.GetTimeDelay(), 6)     // Get Time Delay
                   + ", Elapsed Time: " + String(tonOutput.GetElapsedTime(), 6) // Get Elapsed Time
                   + ", Input: " + String(inputState)            // Input State
                   + ", Output: " + String(outputState));        // Output State
  }
}