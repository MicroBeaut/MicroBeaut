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
  Function: Rising

  Set the Output on the rising edge of Input.

  Member:
  Microbeaut_Rising(void);
  bool Rising(bool Input);

  Declaration:
  Microbeaut_Rising variableName

  Parameters:
  Input:
  Input           : Input

  Return:
  TRUE or FALSE (HIGH/LOW)

  Get Output/Parameters:
  boolVariable = variableName.Output();

  Syntax:
  boolVariable = variableName.Rising(boolInput);

*/
// WokWi: https://wokwi.com/arduino/projects/324033361796399700

#include "MicroBeaut.h"

#define swPin   2               // Define Push Button Pin
#define ledPin  3               // Define LED Pin

MicroBeaut_Rising reInput;     // Rising Edge Variable
bool inputState;                // Input State
bool outputState;               // Output State
int counterValue;


// Serial Plotter Purpose
MicroBeaut_Trigger triggerDisplay;  // Trigger Variable
unsigned long lineNumber;           // Line Number : Max = 9999
const float printPresetTime = 0.100;  // 100 milliseconds

const float timeDelay = 1.0;          // Time Delay 1 second

void setup() {
  Serial.begin(115200);                           // Set Baud Rate
  triggerDisplay.SetTimeDelay(printPresetTime);   // Initial Time Delay for Serial Plotter

  pinMode(swPin, INPUT);              // Input Pin Mode
  pinMode(ledPin, OUTPUT);            // Output Pin Mode
}

void loop() {
  inputState = digitalRead(swPin);              // Read Input State (0 = Release, 1 = Press)
  outputState = reInput.Rising(inputState);     // Rising Edge Function with Input Parameter

  // Counter by Rising Edge Input
  if (outputState) {
    counterValue = counterValue < 15 ? counterValue + 1 : 0;
  }
  digitalWrite(ledPin, outputState);            // ON/OFF LED

  // Trigger for Serial Plotter
  if (triggerDisplay.Trigger(true) | outputState) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber)
                   + ", Input: " + String(inputState)              // Input State
                   + ", Output: " + String(outputState)            // Output State
                   + " :Counter Number: " + String(counterValue)); // Counter Value
  }
}