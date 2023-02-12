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
  void setTimeDelay(uint16_t timeDelay);
  bool readInput(bool pulseInput);
  uint16_t getTimeDelay(void);
  uint16_t getElapsedTime(void);

  Declaration:
  Microbeaut_TimePulse variableName

  Parameters:
  Input:
  Input           : Input
  Time Delay      : Time Delay in Second;

  Return:
  TRUE or FALSE (HIGH/LOW)

  Get Output/Parameters:
  boolVariable = variableName.readStatus();
  floatVariable = variableName.getTimeDelay();    // Return Current Time Time Pulse
  floatVariable = variableName.getElapsedTime();  // Return Elapsed Time

  Syntax:
  variableName.setTimeDelay(floatTimePulse);
  boolVariable = variableName.readInput(boolInput);
*/
// WokWi: https://wokwi.com/arduino/projects/324006931497747028

#include "MicroBeaut.h"

#define inputPin   2               // Define Push Button Pin
#define outputPin  3               // Define LED Pin

bool inputState;  // Input State
bool outputState; // Output State

MicroBeaut_TimePulse timepulseFunction; // Time Pulse Variable
const uint16_t timeDelay = 1000;            // Time Delay 1 second

// Serial Plotter Purpose
MicroBeaut_Trigger triggerPlotter;  // Trigger Variable
unsigned long lineNumber;           // Line Number : Max = 9999
const uint16_t plotterPresetTime = 100;  // 10 milliseconds



void setup() {
  Serial.begin(115200);                           // Set Baud Rate
  triggerPlotter.setTimeDelay(plotterPresetTime);   // Initial Time Delay for Serial Plotter

  pinMode(inputPin, INPUT);              // Input Pin Mode
  pinMode(outputPin, OUTPUT);            // OutputPin Mode
  timepulseFunction.setTimeDelay(timeDelay);  // Set Time Delay
}

void loop() {
  inputState = digitalRead(inputPin);    // Read Input State (0 = Release, 1 = Press)
  outputState = timepulseFunction.readInput(inputState);   // Time Pulse Function with Input Parameter
  digitalWrite(outputPin, outputState); // ON/OFF LED


  // readInput for Serial Plotter
  if (triggerPlotter.readInput(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber)
                   + ":Preset Time: " + String(timepulseFunction.getTimeDelay())     // Get Time Delay
                   + ", Elapsed Time: " + String(timepulseFunction.getElapsedTime()) // Get Elapsed Time
                   + ", Input: " + String(inputState)           // Input State
                   + ", readStatus: " + String(outputState));      // Output State
  }
}