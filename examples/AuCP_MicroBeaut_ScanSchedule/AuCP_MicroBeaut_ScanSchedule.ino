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
  Function:  ScanSchedule
  Purpose:   Schedules execution after a certain number of scans.

  This function can schedule the execution of certain routines when
  a specified number of evaluations has occurred. Output
  is TRUE after the specified number of evaluations, holding TRUE for one
  evaluation. By testing the output, you can cause sections of the
  control program to be executed periodically.

  Member:
  void setScanSchedule(unsigned long numberOfScan, MicroBeaut_CallBackFunction functionName);
  bool readInput(bool enableInput = true);
  uint16_t getElapsedTime(void);

  Declaration:
  Microbeaut_ScanSchedule variableName

  Parameters:
  Input:
  enableInput     : Enable Scan Schedule Function
  NumberOfScan    : Number of scans
  FunctionName    : CallBack Function
  Return:
  TRUE or FALSE (HIGH/LOW)

  Get Output/Parameters:
  boolVariable = variableName.readStatus();
  uint16Variable = variableName.getElapsedTime();

  Syntax:
  variableName.setScanSchedule(numberOfScan, functionName);
  boolVariable = readInput(enableInput);

*/
// WokWi: https://wokwi.com/arduino/projects/324493126851887699

#include "MicroBeaut.h"

#define inputPin    A0  // Define Push Button Pin
#define outputPin   7   // Define LED Pin

bool inputState;  // Input State
bool outputState; // Output State

MicroBeaut_ScanSchedule scanScheduleFunction; // Scan Schedule Function
const unsigned long numberOfScan = 17450;     // Number of scans

// Serial Plotter Purpose
MicroBeaut_Trigger triggerPlotter;    // Trigger Variable
unsigned long lineNumber;             // Line Number : Max = 9999
const uint16_t plotterPresetTime = 100; // 100 milliseconds

void ToggleStateLED();

void setup() {
  Serial.begin(115200);                           // Set Baud Rate
  triggerPlotter.setTimeDelay(plotterPresetTime); // Initial Time Delay for Serial Plotter

  pinMode(inputPin, INPUT);   // Input Pin Mode
  pinMode(outputPin, OUTPUT); // Output Pin Mode

  scanScheduleFunction.setScanSchedule(numberOfScan, ToggleStateLED); // Scan Schedule Function with Enable Input and CallBack Function
}

void loop() {
  inputState = !digitalRead(inputPin);  // Read Input State (0 = Release, 1 = Press)
  scanScheduleFunction.readInput(inputState); // Scan Schedule Function with Enable Parameter

  // Scan Schedule for Serial Plotter
  if (triggerPlotter.readInput(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber)
                   + ", Enable: " + String(inputState)  // Input State
                   + ", Output: " + String(outputState) // Output State
                   + ", Elapsed Scan: " + String(scanScheduleFunction.getElapsedScan()));
  }
}

void ToggleStateLED() {
  outputState = !outputState;
  digitalWrite(outputPin, outputState); // ON/OFF LED
}