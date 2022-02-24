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
   Function:  ScanSchedule
   Purpose:   Schedules execution after a certain number of scans.

   This function can schedule the execution of certain routines when
   a specified number of evaluations has occurred. Output
   is TRUE after the specified number of evaluations, holding TRUE for one
   evaluation. By testing the output, you can cause sections of the
   control program to be executed periodically.

  Member:
    void Setup(unsigned long NumberOfScan, MicroBeaut_CallBackFunction FunctionName);
    bool Run(bool enableInput);
    bool Run(bool enableInput, unsigned long NumberOfScan, MicroBeaut_CallBackFunction FunctionName);
    float Actual(void);

  Declaration:
  Microbeaut_ScanSchedule variableName

  Parameters:
  Input:
    enableInput     : Enable Scan Schedule Function
    NumberOfScan    : Number of scans
    FunctionName    : CallBack Function
  Return:
    TRUE or FALSE (HIGH/LOW)


  Syntax:
  Option 1:
  variableName.Setup(NumberOfScan, functionName);
  boolVariable = Run(enableInput);

  Option 2:
  boolVariable = Run(enableInput, NumberOfScan, functionName);

  Get Parameter:
  floatVariable = variableName.Actual();

*/
//https://wokwi.com/arduino/projects/324032370802950738

#include "MicroBeaut.h"

#define swInputPin    A0        // Define Push Button Pin
#define ledOutputPin  7         // Define LED Pin

MicroBeaut_ScanSchedule scanSchedule;     // Scan Schedule Function
bool inputState;                          // Input State
bool outputState;                         // Output State


// Serial Plotter Purpose
MicroBeaut_Trigger trigDisplay;       // Scan Schedule Variable
unsigned long lineNumber;             // Line Number : Max = 9999
const float printPresetTime = 0.01;   // 10 milliseconds


// TYPE YOUR OPTION (OPTION1-2)
//************************************************************
#define OPTION1                    // Select Option to Compile
//************************************************************

const float numberOfScan = 12000;             // Number of scans

void setup() {
  Serial.begin(115200);                        // Set Baud Rate
  trigDisplay.SetTimeDelay(printPresetTime);   // Initial Time Delay for Serial Plotter


  pinMode(swInputPin, INPUT);             // Input Pin Mode
  pinMode(ledOutputPin, OUTPUT);           // Output Pin Mode

  // Scan Schedule Setup for OPTION 1: Scan Schedule Function with Enable Input
#if defined (OPTION1)
  // Scan Schedule Function with Enable Input and CallBack Function
  scanSchedule.Setup(numberOfScan, ToggleStateLED);
#endif
}

void loop() {

  inputState = digitalRead(swInputPin);  // Read Input State (0 = Release, 1 = Press)

  // Scan Schedule OPTION 1: Scan Schedule Function with Enable Input
#if defined (OPTION1)
  // Scan Schedule Function with Enable Parameter
  scanSchedule.Run(!inputState);


  // Scan Schedule OPTION 2: Scan Schedule Function with All Parameters
#elif defined (OPTION2)
  // Scan Schedule Function with All Parameters
  scanSchedule.Run(!inputState, numberOfScan, ToggleStateLED);
#endif

  digitalWrite(ledOutputPin, outputState); // ON/OFF LED

  // Scan Schedule for Serial Plotter
  if (trigDisplay.Trigger(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber)
                   + ", Input: " + String(!inputState)         // Input State
                   + ", Output: " + String(outputState)       // Output State
                   + ", Actual Time: " + String(scanSchedule.Actual(), 6));
  }
}

void ToggleStateLED()
{
  outputState = !outputState;
}