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
  Function:  Debounce
  The rising edge of input "bounceInput" starts a timer of duration "timeDebounce".
  When the elapsed time is greater than or equal to "timeDebounce",
  the timer stops, and output changes from FALSE to TRUE.

  The falling edge of input "bounceInput" starts a timer of duration "timeDebounce".
  When the elapsed time is greater than or equal to "timeDebounce",
  the timer stops and output changes from TRUE to FALSE.

  Member:
  void SetTimeDebounce(float timeDebounce = 0.01);
  bool Debounce(bool bounceInput);
  float GetTimeDebounce(void);
  float GetElapsedTime(void);

  Declaration:
  MicroBeaut_Debounce variableName

  Parameters:
  Input:
  Input           : Input
  Time Debounce   : Time Debounce in Second : Default = 10 milliseconds

  Return:
  TRUE or FALSE (HIGH/LOW)

  Get Output/Parameters:
  boolVariable = variableName.Output();           // Return Current Output State
  floatVariable = variableName.GetTimeDebounce();    // Return Current Time Debounce
  floatVariable = variableName.GetElapsedTime();  // Return Elapsed Time


  Syntax:
  variableName.SetTimeDebounce(floatTimeDebounce);
  boolVariable = variableName.Debounce(bounceInput);

*/
// WokWi: https://wokwi.com/arduino/projects/323857211998601812

#include "MicroBeaut.h"

#define inputPin   2  // Define Push Button Pin
#define outputPin  3  // Define LED Pin

bool inputState;  // Input State
bool outputState; // Output State

MicroBeaut_Debounce  debounceFunction;  // Debounce Variable
const float timeDebounce = 0.01;        // TimeDebounce 10 milliseconds

// Serial Plotter Purpose
MicroBeaut_Trigger triggerPlotter;    // Trigger Variable
unsigned long lineNumber;             // Line Number : Max = 999
const float plotterPresetTime = 0.01; // 10 milliseconds

void setup() {
  Serial.begin(115200); // Set Baud Rate
  triggerPlotter.SetTimeDelay(plotterPresetTime); // Initial Time Delay for Serial Plotter

  pinMode(inputPin, INPUT);              // Input Pin Mode
  pinMode(outputPin, OUTPUT);            // Output Pin Mode
  debounceFunction.SetTimeDebounce(timeDebounce); // Set Time Debounce
}

void loop() {
  inputState = digitalRead(inputPin);   // Read Input State (0 = Release, 1 = Press)
  outputState = debounceFunction.Debounce(inputState);  // Debounce Function with Input Parameter
  digitalWrite(outputPin, outputState); // ON/OFF LED

  // Trigger for Serial Plotter
  if (triggerPlotter.Trigger(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber) + ":Time Debounce: " + String(debounceFunction.GetTimeDebounce(), 6) // Get Time Debounce
                   + ", Elapsed Time: " + String(debounceFunction.GetElapsedTime(), 6) // Get Elapsed Time
                   + ", Input: " + String(inputState)      // Input State
                   + ", Output: " + String(outputState));  // Output State
  }
}