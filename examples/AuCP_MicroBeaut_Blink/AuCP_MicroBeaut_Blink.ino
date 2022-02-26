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
  Function: MicroBeaut_Blink
  Input "Input" enables blinking. Input "TimeDelayOn"
  gives the minimum time that the output is TRUE.
  Input "TimeDelayrOff" gives the minimum time that the output is FALSE.
  The output does not change if "Input" is FALSE.

  Blink Member:
  void SetTimeDelay(float TimeDelay);
  void SetTimeDelay(float TimeDelayOff, float TimeDelayOn);
  bool Blink(bool Input);
  bool Blink(bool Input, float TimeDelay);
  bool Blink(bool, float TimeDelayOff, float TimeDelayOn);
  float GetTimeDelayOn(void);
  float GetTimeDelayOff(void);
  float GetElapsedTime(void);
  bool Output(void);

  Declaration:
  MicroBeaut_Blink variableName

  Parameters:
  Input:
    Input           : Enables Blinking
    Time Delay      : OFF/ON Time Delay in Second
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
  Option 1:
    variableName.SetTimeDelay(floatTimeDelayOnOff);
    boolVariable = variableName.Blink(inputVariable);

  Option 2:
    variableName.SetTimeDelay(floatTimeDelayOff, floatTimeDelayOn);
    boolVariable = variableName.Blink(inputVariable);

  Option 3:
    boolVariable = variableName.Blink(inputVariable, floatTimeDelayOnOff);

  Option 4:
    boolVariable = variableName.Blink(floatTimeDelayOff, floatTimeDelayOn);


*/
// WokWi: https://wokwi.com/arduino/projects/323848037323506259

#include "MicroBeaut.h"

#define pbPin       2               // Define Push Button Pin
#define ledPin      3               // Define LED Pin

MicroBeaut_Blink  blinkOutput;      // Blink Variable
bool disableState;                  // Disable State
bool outputState;                   // Output State


// Serial Plotter Purpose
MicroBeaut_Trigger triggerDisplay;    // Trigger Variable
unsigned long lineNumber;             // Line Number : Max = 999
const float printPresetTime = 0.010;  // Trigger Time = 10 milliseconds


const float timeDelay = 0.5;     // Blink 500 milliseconds
const float timeDelayOff = 0.5;   // OFF: 500 milliseconds
const float timeDelayOn = 1.0;    // ON: 1 second


// TYPE YOUR OPTION (OPTION1-4)
//************************************************************
#define OPTION1                   // Select Option to Compile
//************************************************************

void setup() {
  Serial.begin(115200);                           // Set Baud Rate
  triggerDisplay.SetTimeDelay(printPresetTime);   // Initial Time Delay for Serial Plotter

  pinMode(pbPin, INPUT_PULLUP);                   // Input Pin Mode
  pinMode(ledPin, OUTPUT);                        // Output Pin Mode
}

void loop() {

  disableState = digitalRead(pbPin);                // Read Disable State (0 = Press, 1 = Release)

  // Blink OPTION 1
  // 1. Setup Time Delay for both ON/OFF
  // 2. Blink Function with Input
#if defined (OPTION1)
  blinkOutput.SetTimeDelay(timeDelay);            // Set Time Delay OFF/ON same delay time
  outputState = blinkOutput.Blink(disableState);     // Blink Function with Input Parameter
  digitalWrite(ledPin, outputState);               // ON/OFF LED

  // Blink OPTION 2:
  // 1. Setup Time Delay On and Time Delay Off
  // 2. Blink Function with Input
#elif defined (OPTION2)
  blinkOutput.SetTimeDelay(timeDelayOff, timeDelayOn);  // Set Time Delay OFF/ON individual
  outputState = blinkOutput.Blink(disableState);           // Blink Function with Input Parameter
  digitalWrite(ledPin, outputState);                     // ON/OFF LED

  // Blink OPTION 3: Blink Function with Input and Time Delay for both OFF/ON
#elif defined (OPTION3)
  outputState = blinkOutput.Blink(disableState, timeDelay);   // Blink Function with Input and Time Delay OFF/ON Parameter
  digitalWrite(ledPin, outputState);                     // ON/OFF LED

  // Blink OPTION 4: Blink Function with Input, Time Delay Off, and Time Delay On
#elif defined (OPTION4)
  outputState = blinkOutput.Blink(disableState, timeDelayOff, timeDelayOn);   // Blink Function with Input and Time Delay OFF/ON Parameter
  digitalWrite(ledPin, outputState);                                     // ON/OFF LED
#endif

  // Trigger for Serial Plotter
  if (triggerDisplay.Trigger(true)) {
    lineNumber = lineNumber < 999 ? lineNumber + 1 : 1;
    Serial.println("L" + String(lineNumber) + ": Time Delay OFF: " + String(blinkOutput.GetTimeDelayOff(), 6)     // Get Time Delay ON
                   + ", Time Delay ON: " + String(blinkOutput.GetTimeDelayOn(), 6) // Get Time Delay OFF
                   + ", Elapsed Time: " + String(blinkOutput.GetElapsedTime(), 6) // Get Elapsed Time
                   + ", Enable: " + String(disableState)      // Disable State
                   + ", Output: " + String(outputState));  // Output State
  }
}