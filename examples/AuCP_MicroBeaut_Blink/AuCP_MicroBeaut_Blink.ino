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
  Function: MicroBeaut_Blink
  Input "enableInput" enables blinking. Input "TimeDelayOn"
  gives the minimum time that the output is TRUE.
  Input "TimeDelayrOff" gives the minimum time that the output is FALSE.
  The output does not change if "enableInput" is FALSE.

  Blink Member:
  void SetTimeDelay(float timeDelayOff, float timeDelayOn);
  bool Blink(bool enableInput = true);
  float GetTimeDelayOn(void);
  float GetTimeDelayOff(void);
  float GetElapsedTime(void);
  bool Output(void);

  Declaration:
  MicroBeaut_Blink variableName

  Parameters:
  Input:
    Input           : Enables Blinking
    Time Delay On   : ON Time Delay in Second
    Time Delay Off  : OFF Time Delay in Second

  Return:
    TRUE or FALSE (HIGH/LOW)

  Get Output/Parameters:
    boolVariable = variableName.Output();             // Return current Output State
    floatVariable = variableName.GetTimeDelayOn();    // Return Current Time Delay On
    floatVariable = variableName.GetTimeDelayOff();   // Return Current Time Delay Off
    floatVariable = variableName.GetElapsedTime();    // Return Elapsed Time

  Syntax:
    variableName.SetTimeDelay(floatTimeDelayOff, floatTimeDelayOn);
    boolVariable = variableName.Blink(boolInput);
*/
// WokWi: https://wokwi.com/arduino/projects/323848037323506259

#include "MicroBeaut.h"

#define inputPin       2 // Define Push Button Pin
#define outputPin      3 // Define LED Pin

bool inputState;  // Disable State
bool outputState; // Output State

MicroBeaut_Blink  blinkFunction;  // Blink Variable
const float timeDelayOff = 0.5;   // OFF: 500 milliseconds
const float timeDelayOn = 1.0;    // ON: 1 second


// Serial Plotter Purpose
MicroBeaut_Trigger triggerPlotter;      // Trigger Variable
unsigned long lineNumber;               // Line Number : Max = 999
const float plotterPresetTime = 0.010;  // Trigger Time = 10 milliseconds

void setup() {
  Serial.begin(115200);                           // Set Baud Rate
  triggerPlotter.SetTimeDelay(plotterPresetTime); // Initial Time Delay for Serial Plotter

  pinMode(inputPin, INPUT_PULLUP);  // Input Pin Mode
  pinMode(outputPin, OUTPUT);       // Output Pin Mode
  blinkFunction.SetTimeDelay(timeDelayOff, timeDelayOn);  // Set Time Delay OFF/ON individual
}

void loop() {

  inputState = digitalRead(inputPin);             // Read Disable State (0 = Press, 1 = Release)
  outputState = blinkFunction.Blink(inputState);  // Blink Function with Input Parameter
  digitalWrite(outputPin, outputState);           // ON/OFF LED


  // Trigger for Serial Plotter
  if (triggerPlotter.Trigger(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber) + ": Time Delay OFF: " + String(blinkFunction.GetTimeDelayOff(), 6) // Get Time Delay ON
                   + ", Time Delay ON: " + String(blinkFunction.GetTimeDelayOn(), 6)  // Get Time Delay OFF
                   + ", Elapsed Time: " + String(blinkFunction.GetElapsedTime(), 6)   // Get Elapsed Time
                   + ", Enable: " + String(inputState)    // Disable State
                   + ", Output: " + String(outputState)); // Output State
  }
}