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

  readInput Member:
  void setTimeDelay(uint16_t timeDelayOff, uint16_t timeDelayOn);
  bool readInput(bool enableInput = true);
  uint16_t getTimeDelayOn(void);
  uint16_t getTimeDelayOff(void);
  uint16_t getElapsedTime(void);
  bool readStatus(void);

  Declaration:
  MicroBeaut_Blink variableName

  Parameters:
  Input:
    Input           : Enables Blinking
    Time Delay On   : ON Time Delay in Milliseconds
    Time Delay Off  : OFF Time Delay in Milliseconds

  Return:
    TRUE or FALSE (HIGH/LOW)

  Get Output/Parameters:
    boolVariable = variableName.readStatus();         // Return current Output State
    uint16Variable = variableName.getTimeDelayOn();    // Return Current Time Delay On
    uint16Variable = variableName.getTimeDelayOff();   // Return Current Time Delay Off
    uint16Variable = variableName.getElapsedTime();    // Return Elapsed Time

  Syntax:
    variableName.setTimeDelay(uint16TimeDelayOff, uint16TimeDelayOn);
    boolVariable = variableName.readInput(boolInput);
*/
// WokWi: https://wokwi.com/arduino/projects/323848037323506259

#include "MicroBeaut.h"

#define inputPin       2 // Define Push Button Pin
#define outputPin      3 // Define LED Pin

bool inputState;  // Disable State
bool outputState; // Output State

MicroBeaut_Blink  blinkFunction;      // Blink Variable
const uint16_t timeDelayOff = 500;    // OFF: 500 milliseconds
const uint16_t timeDelayOn = 1000;    // ON: 1 second

// Serial Plotter Purpose
MicroBeaut_Trigger triggerPlotter;      // Trigger Variable
unsigned long lineNumber;               // Line Number : Max = 999
const uint16_t plotterPresetTime = 10;  // Trigger Time = 10 milliseconds

void setup() {
  Serial.begin(115200);                           // Set Baud Rate
  triggerPlotter.setTimeDelay(plotterPresetTime); // Initial Time Delay for Serial Plotter

  pinMode(inputPin, INPUT_PULLUP);  // Input Pin Mode
  pinMode(outputPin, OUTPUT);       // Output Pin Mode
  blinkFunction.setTimeDelay(timeDelayOff, timeDelayOn);  // Set Time Delay OFF/ON individual
}

void loop() {
  inputState = digitalRead(inputPin);                 // Read Disable State (0 = Press, 1 = Release)
  outputState = blinkFunction.readInput(inputState);  // Blink Function with Input Parameter
  digitalWrite(outputPin, outputState);               // ON/OFF LED

  // readInput for Serial Plotter
  if (triggerPlotter.readInput(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber) + ": Time Delay OFF: " + String(blinkFunction.getTimeDelayOff()) // Get Time Delay ON
                   + ", Time Delay ON: " + String(blinkFunction.getTimeDelayOn())  // Get Time Delay OFF
                   + ", Elapsed Time: " + String(blinkFunction.getElapsedTime())   // Get Elapsed Time
                   + ", Enable: " + String(inputState)    // Disable State
                   + ", readStatus: " + String(outputState)); // Output State
  }
}