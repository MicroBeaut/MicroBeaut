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
  Function: TimerOn

  The rising edge of input "timerOnInput" starts a timer of duration "TimeDelay".
  When the elapsed time is greater than or equal to "TimeDelay",
  the timer stops, and output changes from FALSE to TRUE.
  The next falling edge of the input "timerOnInput" initializes the timer.

  Member:
  void setTimeDelay(uint16_t timeDelay);
  bool readInput(bool timerOnInput);
  uint16_t GetTimeDelay(void);
  uint16_t GetElapsedTime(void);

  Declaration:
  MicroBeaut_TimerOn variableName

  Parameters:
  Input:
  Input           : Input
  Time Delay      : Time Delay in Second;

  Return:
  TRUE or FALSE (HIGH/LOW)

  Get Output/Parameters:
  boolVariable = variableName.readStatus();
  floatVariable = variableName.GetTimeDelay();    // Return Current Time Timer On
  floatVariable = variableName.GetElapsedTime();  // Return Elapsed Time

  Syntax:
  variableName.setTimeDelay(floatTimeDelayOn);
  boolVariable = variableName.readInput(boolInput);

*/
// WokWi: https://wokwi.com/arduino/projects/324001504402866770

#include "MicroBeaut.h"

#define inputPin   2  // Define Push Button Pin
#define outputPin  3  // Define LED Pin

bool inputState;      // Input State
bool outputState;     // Output State

MicroBeaut_TimerOn tonOutput; // Timer On Variable
const uint16_t timeDelay = 1000;  // Time Delay 1 second

// Serial Plotter Purpose
MicroBeaut_Trigger triggerPlotter;      // Trigger Variable
unsigned long lineNumber;               // Line Number : Max = 9999
const uint16_t plotterPresetTime = 10;  // 10 milliseconds

void setup() {
  Serial.begin(115200);                             // Set Baud Rate
  triggerPlotter.setTimeDelay(plotterPresetTime);   // Initial Time Delay for Serial Plotter

  pinMode(inputPin, INPUT);     // Input Pin Mode
  pinMode(outputPin, OUTPUT);   // Output Pin Mode
  tonOutput.setTimeDelay(timeDelay);  // Set Time Delay
}

void loop() {
  inputState = digitalRead(inputPin);           // Read Input State (0 = Release, 1 = Press)
  outputState = tonOutput.readInput(inputState);  // Timer On Function with Input Parameter
  digitalWrite(outputPin, outputState);         // ON/OFF LED


  // readInput for Serial Plotter
  if (triggerPlotter.readInput(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber)
                   + ":Preset Time: " + String(tonOutput.getTimeDelay())     // Get Time Delay
                   + ", Elapsed Time: " + String(tonOutput.getElapsedTime()) // Get Elapsed Time
                   + ", Input: " + String(inputState)            // Input State
                   + ", readStatus: " + String(outputState));        // Output State
  }
}