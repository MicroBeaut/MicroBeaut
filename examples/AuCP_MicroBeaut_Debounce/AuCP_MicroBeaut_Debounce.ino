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
  Function:  Debounce
  The rising edge of input "Input" starts a timer of duration "TimeDelay".
  When the elapsed time is greater than or equal to "TimeDelay",
  the timer stops, and output changes from FALSE to TRUE.

  The falling edge of input "Input" starts a timer of duration "TimeDelay".
  When the elapsed time is greater than or equal to "TimeDelay",
  the timer stops and output changes from TRUE to FALSE.

  Member:
  MicroBeaut_Debounce(void);
  void SetTimeDelay(float TimeDelay);
  bool Debounce(bool Input);
  bool Debounce(bool Input, float TimeDelay);
  float GetTimeDelay(void);
  float GetElapsedTime(void);

  Declaration:
  MicroBeaut_Debounce variableName

  Parameters:
  Input:
  Input           : Input
  Time Delay      : Time Debounce in Second : Default = 10 milliseconds

  Return:
  TRUE or FALSE (HIGH/LOW)

  Get Output/Parameters:
  boolVariable = variableName.Output();                        // Return Current Output State
  floatVariable = variableName.GetTimeDelay();    // Return Current Time Debounce
  floatVariable = variableName.GetElapsedTime();  // Return Elapsed Time


  Syntax:
  Option 1:
  variableName.SetTimeDelay(floatTimeDebounce);
  boolVariable = variableName.Debounce(inputVariable);

  Option 2:
  boolVariable = variableName.Debounce(inputVariable, floatTimeDebounce);



*/
// WokWi: https://wokwi.com/arduino/projects/323857211998601812

#include "MicroBeaut.h"

#define swPin   2                   // Define Push Button Pin
#define ledPin  3                   // Define LED Pin

MicroBeaut_Debounce  debounceSW;    // Debounce Variable
bool inputState;                    // Input State
bool outputState;                   // Output State


// Serial Plotter Purpose
MicroBeaut_Trigger triggerDisplay;  // Trigger Variable
unsigned long lineNumber;           // Line Number : Max = 999
const float printPresetTime = 0.01; // 10 milliseconds


// TYPE YOUR OPTION (OPTION1-2)
//************************************************************
#define OPTION1                   // Select Option to Compile
//************************************************************

// To Test Debounce at 1 second
const float timeDebounce = 1.0;      // TimeDebounce 1 second

void setup() {
  Serial.begin(115200);                           // Set Baud Rate
  triggerDisplay.SetTimeDelay(printPresetTime);   // Initial Time Delay for Serial Plotter

  pinMode(swPin, INPUT);              // Input Pin Mode
  pinMode(ledPin, OUTPUT);            // Output Pin Mode
}

void loop() {

  inputState = digitalRead(swPin);    // Read Input State (0 = Release, 1 = Press)

  // Debounce OPTION 1
  // 1. Setup Time Delay for Debounce
  // 2. Debounce Function with Input
#if defined (OPTION1)
  debounceSW.SetTimeDelay(timeDebounce);          // Set Time Debounce
  outputState = debounceSW.Debounce(inputState);  // Debounce Function with Input Parameter
  digitalWrite(ledPin, outputState);              // ON/OFF LED

  // Debounce OPTION 2: Debounce Function with Input
#elif defined (OPTION2)
  outputState = debounceSW.Debounce(inputState, timeDebounce);  // Debounce Function with Input Parameter
  digitalWrite(ledPin, outputState);                            // ON/OFF LED
#endif

  // Trigger for Serial Plotter
  if (triggerDisplay.Trigger(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber) + ":Time Debounce: " + String(debounceSW.GetTimeDelay(), 6) // Get Time Debounce
                   + ", Elapsed Time: " + String(debounceSW.GetElapsedTime(), 6) // Get Elapsed Time
                   + ", Input: " + String(inputState)      // Input State
                   + ", Output: " + String(outputState));  // Output State

  }
}