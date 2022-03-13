# Applied Microcontroller Programming (AµCP)
Applied PLC's Technique, Concept, and Function to Microcontroller is named "Applied Microcontroller Programming" and shared my Libraries "MicroBeaut" with you.

### 1. Timer
- Debounce
- TimerOn (Timer On)
- TimerOff (Timer Off)
- TimePulse (Time Pulse)
- Blink
- Trigger
### 2. Bistable
-   SR (Set Dominant)
-   RS (Reset Dominant)
-   Toggle
### 3. Edge
-   Rising (Rising Edge)
-   Falling (Falling Edge)
### 4. Schedule
-   TimeSchedule (Schedule execution at specified time intervals)
-   ScanSchedule (Schedules execution after a certain number of scans)

All of them are generic functions that can help you do Microcontroller Programming efficiently.

Timer Group used "micros()" of Arduino function for calculating elapsed time. As I call " Continuous" tasks, you can use them for multitasking programs. Still, don't forget a delay() function; you may sometimes require to use it as an initiative of some process.

Bistable and Edge Group are essential functions to detect or turn bit On / Off. Without thinking about managing their program, you can use these libraries in your program.

The Schedule is a choice for your to execute your subroutine by Time or Scans.

I hope you will enjoy Microcontroller Programming and hope these libraries may help you manage your program easily.

----

# Timer

## Debounce

The debounce function delays TimeDebounce from the rising edge and falling edge of input to the output's rising edge and falling edge.

The rising edge of the input starts the timer. While the input is TRUE, after a delay of duration TimeDebounce, the timer changes the output to TRUE.
The falling edge of the input starts the timer. While the input is FALSE, after a delay of duration TimeDebounce, the timer changes the output to FALSE.

### `Syntax:`

#### `Declaration`
```C
MicroBeaut_Debounce variableFunction;
```
#### `Function Use`
```C
variableFunction.SetTimeDebounce(floatTimeDebounceInSecond);
boolReturnValue = variableFunction.Debounce(boolVariableInput);
```
#### `Getting other values from Function`

##### `Output State`
```C
boolReturnOutput = variableFunction.Output();
```
##### `Time Debounce Setting`
```C
floatReturnTimeDelayInSecond = variableFunction.GetTimeDebounce();
```
##### `Elapsed Time`
```C
floatReturnElapsedTimeInSecond = variableFunction.GetElapsedTime();
```

### Example:
```C
#include "MicroBeaut.h"


#define inputPin 8  // Define Input Pin

MicroBeaut_Debounce debFunction;  // Debounce Variable
bool inputState;    // Input State
bool prevInput;     // Previous Input State
bool outputState;   // Output State

const float timeDebounce = 0.01;  // Time Debounce = 10 milliseconds

void setup() {
	pinMode(inputPin, INPUT);                // Set Pin as an Input Mode
	pinMode(LED_BUILTIN, OUTPUT);            // Set Pin as an Output Mode
	debFunction.SetTimeDebounce(timeDebounce);  // Set Time Debounce
}

void loop() {
	prevInput = inputState;                                    // Previous Input = Current Input
	inputState = debFunction.Debounce(digitalRead(inputPin));  // Read Input and Debounce
	outputState ^= (inputState & !prevInput);                  // Toggle Output
	digitalWrite(LED_BUILTIN, outputState);                    // Write Output
}
```

## TimerOn (Timer On)
The timer on function delays TimeDelay from the input's rising edge to the output's rising edge.

The rising edge of the input starts the timer. While the input is TRUE, after a delay of duration TimeDelay, the timer changes the output to TRUE. If the input changes to FALSE at any time, the timer resets, reversing the result to FALSE and elapsed time to zero.


### Syntax:

#### `Declaration`
```C
MicroBeaut_TimeOn variableFunction;
```
#### `Function Use`
```C
variableFunction.SetTimeDelay(floatTimeDelayInSecond);
boolReturnValue = variableFunction.TimerOn(boolVariableInput);
```

#### `Getting other values from Function`

##### `Output State`
```C
boolReturnOutput = variableFunction.Output();
```
##### `Time Delay Setting`
```C
floatReturnTimeDelayInSecond = variableFunction.GetTimeDelay();
```
##### `Elapsed Time`
```C
floatReturnElapsedTimeInSecond = variableFunction.GetElapsedTime();
```

### Example:

```C
#include "MicroBeaut.h"


#define inputPin 8  // Define Input Pin

MicroBeaut_TimerOn tonFunction; // Timer On Variable
bool inputState;  // Input State
bool outputState; // Output State

const float timeDelay = 1.0;  // Time Delay = 1 Second

void setup() {
	pinMode(inputPin, INPUT);     // Set Pin as an Input Mode
	pinMode(LED_BUILTIN, OUTPUT); // Set Pin as an Output Mode
	tonFunction.SetTimeDelay(timeDelay);  // Set Time Delay
}

void loop() {
	inputState = digitalRead(inputPin); // Read Input
	outputState = tonFunction.TimerOn(inputState);  // Timer On Function with Input
	digitalWrite(LED_BUILTIN, outputState);         // Write Output
}
```

## TimerOff (Timer Off)
The timer off function delays TimeDelay from the input's falling edge to the output's falling edge.

The falling edge of the input starts the timer. While the input is FALSE, after a delay of duration TimeDelay, the timer changes the output to FALSE. If the input changes to TRUE at any time, the timer resets, reversing the result to TRUE and elapsed time to zero.
### Syntax:

#### `Declaration`
```C
MicroBeaut_TimeOn variableFunction;
```
#### `Function Use`

```C
variableFunction.SetTimeDelay(floatTimeDelayInSecond);
boolReturnValue = variableFunction.TimerOff(boolVariableInput);
```

#### `Getting other values from Function`

##### `Output State`
```C
boolReturnOutput = variableFunction.Output();
```
##### `Time Delay Setting`
```C
floatReturnTimeDelayInSecond = variableFunction.GetTimeDelay();
```
##### `Elapsed Time`
```C
floatReturnElapsedTimeInSecond = variableFunction.GetElapsedTime();
```

### Example:
```C
#include "MicroBeaut.h"


#define inputPin 8  // Define Input Pin

MicroBeaut_TimerOff tofFunction;  // Timer Off Variable
bool inputState;    // Input State
bool outputState;   // Output State

const float timeDelay = 1.0;      // Time Delay = 1 Second

void setup() {
	pinMode(inputPin, INPUT_PULLUP);      // Set Pin as an Input Mode
	pinMode(LED_BUILTIN, OUTPUT);         // Set Pin as an Output Mode
	tofFunction.SetTimeDelay(timeDelay);  // Set Time Delay
}

void loop() {
	inputState = digitalRead(inputPin);     // Read Input
	outputState = tofFunction.TimerOff(inputState); // Timer Off Function with Input
	digitalWrite(LED_BUILTIN, outputState); // Write Output
}
```

##  TimePulse (Time Pulse)
The time pulse function generates a pulse of duration TimeDelay starting on the rising edge of the input.

The rising edge of the input starts the timer, setting output to TRUE. While the output is TRUE, the timer ignores the input.

### `Syntax:`

#### `Declaration`
```C
MicroBeaut_TimePulse variableFunction;
```
#### `Function Use`
```C
variableFunction.SetTimeDelay(floatTimeDelayInSecond);
boolReturnValue = variableFunction.TimePulse(boolVariableInput);
```

#### `Getting other values from Function`

##### `Output State`
```C
boolReturnOutput = variableFunction.Output();
```
##### `Time Pulse Setting`
```C
floatReturnTimeDelayInSecond = variableFunction.GetTimeDelay();
```
##### `Elapsed Time`
```C
floatReturnElapsedTimeInSecond = variableFunction.GetElapsedTime();
```

### Example:

```C
#include "MicroBeaut.h"


#define inputPin 8  // Define Input Pin

MicroBeaut_TimePulse tpFunction;  // Time Pulse Variable
bool inputState;    // Input State
bool outputState;   // Output State

const float timeDelay = 1.0;  // Time Pulse = 1 Second

void setup() {
	pinMode(inputPin, INPUT);     // Set Pin as an Input Mode
	pinMode(LED_BUILTIN, OUTPUT); // Set Pin as an Output Mode
	tpFunction.SetTimeDelay(timeDelay); // Set Time Pulse
}

void loop() {
	inputState = digitalRead(inputPin);     // Read Input
	outputState = tpFunction.TimePulse(inputState); // Time Pulse Function with Input
	digitalWrite(LED_BUILTIN, outputState); // Write Output
}
```

##  Blink
The input enables blinking. The blink function generates a pulse output that is supposed to repeatedly turn the result on and off. The reset input resets the output to FALSE and initiates the pulse-off period. TimeDelayOn specifies how long the pulse is on; TimeDelayOff specifies how long the pulse is off.

### `Syntax:`

#### `Declaration`
```C
MicroBeaut_Blink variableFunction;
```
#### `Function Use`

```C
variableFunction.SetTimeDelay(floatTimeDelayOffInSecond, floatTimeDelayOnInSecond);
boolReturnValue = variableFunction.Blink(boolVariableInput = true);
```

#### `Getting other values from Function`

##### `Output State`
```C
boolReturnOutput = variableFunction.Output();
```
##### `Time Blink Setting`
```C
floatReturnTimeDelayInSecond = variableFunction.GetTimeDelay();
```
##### `Elapsed Time`
```C
floatReturnElapsedTimeInSecond = variableFunction.GetElapsedTime();
```

### Example:

```C
#include "MicroBeaut.h"


#define inputPin 8  // Define Input Pin

MicroBeaut_Blink blinkFunction;   // Blink Variable
bool enableState;   // Enable State (0 = Disable, 1=Enable)
bool outputState;   // Output State

const float timeDelayOff = 0.25;  // OFF Delay = 0.25 second
const float timeDealyOn = 0.5;    // ON Delay = 0.5 second

void setup() {
	pinMode(inputPin, INPUT_PULLUP);  // Set Pin as an Input Mode
	pinMode(LED_BUILTIN, OUTPUT);     // Set Pin as an Output Mode
	blinkFunction.SetTimeDelay(timeDelayOff, timeDealyOn);  // Set Blink
}

void loop() {
	enableState = digitalRead(inputPin);    // Read Input (0 = Disable, 1 = Enable)
	outputState = blinkFunction.Blink(enableState); // Blink Function with Enable Input
	digitalWrite(LED_BUILTIN, outputState); // Write Output
}
```

### Trigger
The trigger function sets the output only one scan.

The rising edge of the input starts the timer. While the input is TRUE, after a delay of duration TimeDelay, the timer changes the output to TRUE and restarts the timer. If the input changes to FASE at any time, the timer holds the last value.

The reset input resets the output to FALSE and resets the timer.

### `Syntax:`

#### `Declaration`
```C
MicroBeaut_Trigger variableFunction;
```
#### `Function Use`

```C
variableFunction.SetTimeDelay(floatTimeDelayInSecond);
boolReturnValue = variableFunction.Trigger(boolVariableInput = true, boolVariableReset = false);
```

#### `Getting other values from Function`

##### `Output State`
```C
boolReturnOutput = variableFunction.Output();
```
##### `Time Delay Setting`
```C
floatReturnTimeDelayInSecond = variableFunction.GetTimeDelay();
```
##### `Elapsed Time`
```C
floatReturnElapsedTimeInSecond = variableFunction.GetElapsedTime();
```

### Example:

```C
#include "MicroBeaut.h"


#define inputPin 8  // Define Input Pin
#define resetPin 9  // Define Input Pin

MicroBeaut_Trigger trigFunction;  // Trigger Variable
bool inputState;    // Input State
bool resetState;    // Input State
bool outputState;   // Output State
bool trigState;     // Trigger State

const float timeDelay = 1.0;  // Trigger Delay = 1 Second

void setup() {
	Serial.begin(115200);
	pinMode(inputPin, INPUT_PULLUP);  // Set Pin as an Input Mode
	pinMode(resetPin, INPUT);         // Set Pin as an Input Mode
	pinMode(LED_BUILTIN, OUTPUT);     // Set Pin as an Output Mode
	trigFunction.SetTimeDelay(timeDelay); // Set Trigger Delay
}

void loop() {
	inputState = digitalRead(inputPin);     // Read Input
	resetState = digitalRead(resetPin);     // Read Input
	outputState = trigFunction.Trigger(inputState, resetState); // Trigger Function with Input
	digitalWrite(LED_BUILTIN, outputState); // Write Output
	if(trigFunction.Output()) {
		Serial.println("Applying MicroBeaut to your program will make it easier to manage your Multitasking Programming.");
	}
}
```

# Bistable

## SR (Set Dominant)
The RS function block is a latch with the reset input dominant over the set input. The reset input resets output to false. The set input sets the output to TRUE if reset is FALSE. If reset is FALSE and set is FALSE, the output does not change.

### `Syntax:`

#### `Declaration`
```C
MicroBeaut_SR variableFunction;
```

#### `Function Use`
```C
boolReturnValue = variableFunction.SR(boolVariableSet, boolVariableReset);
```

#### `Getting another value from Function`

##### `Output State`
```C
boolReturnOutput = variableFunction.Output();
```

### Example:

```C
#include "MicroBeaut.h"


#define setPin 8    // Define Input Pin
#define resetPin 9  // Define Input Pin

MicroBeaut_SR srFunction; // SR Variable
bool setState;      // Input State
bool resetState;    // Input State
bool outputState;   // Output State


void setup() {
	pinMode(setPin, INPUT_PULLUP);  // Set Pin as an Input Mode
	pinMode(resetPin, INPUT);       // Set Pin as an Input Mode
	pinMode(LED_BUILTIN, OUTPUT);   // Set Pin as an Output Mode
}

void loop() {
	setState = digitalRead(setPin);         // Read Input
	resetState = digitalRead(resetPin);     // Read Input
	outputState = srFunction.SR(setState, resetState); // SR Function with Set and Reset
	digitalWrite(LED_BUILTIN, outputState); // Write Output
}
```

## RS (Reset Dominant)

The RS function is a latch with the reset input dominant over the set input. The
reset input resets output to FALSE. The set input sets output to TRUE if reset is false. If reset is FALSE and
S is FASE, then Q1 does not change.

### `Syntax:`

#### `Declaration`
```C
MicroBeaut_RS variableFunction;
```

#### `Function Use`
```C
boolReturnValue = variableFunction.RS(boolVariableSet, boolVariableReset);
```

#### `Getting another value from Function`

##### `Output State`
```C
boolReturnOutput = variableFunction.Output();
```

### Example:

```C
#include "MicroBeaut.h"


#define setPin 8    // Define Input Pin
#define resetPin 9  // Define Input Pin

MicroBeaut_RS rsFunction; // RS Variable
bool setState;      // Input State
bool resetState;    // Input State
bool outputState;   // Output State


void setup() {
	pinMode(setPin, INPUT_PULLUP);  // Set Pin as an Input Mode
	pinMode(resetPin, INPUT);       // Set Pin as an Input Mode
	pinMode(LED_BUILTIN, OUTPUT);   // Set Pin as an Output Mode
}

void loop() {
	setState = digitalRead(setPin);       // Read Input
	resetState = digitalRead(resetPin);   // Read Input
	outputState = rsFunction.RS(setState, resetState); // RS Function with Set and Reset
	digitalWrite(LED_BUILTIN, outputState); // Write Output
}
```

## Toggle

The rising edge of input "Input" toggles Output. Input "Reset" resets Output (to FALSE).

### `Syntax:`

#### `Declaration`
```C
MicroBeaut_Toggle variableFunction;
```



#### `Function Use`
```C
boolReturnValue = variableFunction.Toggel(boolVariableInput, boolVariableReset = false);
```

#### `Getting another value from Function`

##### `Output State`
```C
boolReturnOutput = variableFunction.Output();
```

### Example:

```C
#include "MicroBeaut.h"


#define inputPin 8  // Define Input Pin
#define resetPin 9  // Define Input Pin

MicroBeaut_Toggle togFunction;  // RS Variable
bool inputState;    // Input State
bool resetState;    // Input State
bool outputState;   // Output State


void setup() {
	pinMode(inputPin, INPUT_PULLUP);  // Set Pin as an Input Mode
	pinMode(resetPin, INPUT);         // Set Pin as an Input Mode
	pinMode(LED_BUILTIN, OUTPUT);     // Set Pin as an Output Mode
}

void loop() {
	inputState = digitalRead(inputPin);     // Read Input
	resetState = digitalRead(resetPin);     // Read Input
	outputState = togFunction.Toggle(inputState, resetState); // Toggle Function with Input and Reset
	digitalWrite(LED_BUILTIN, outputState); // Write Output
}
```

---

# Edge

## Rising (Rising Edge)

Set Output on the rising edge of Input.

### `Syntax:`

#### `Declaration`
```C
MicroBeaut_Rising variableFunction;
```
#### `Function Use`

```C
boolReturnValue = variableFunction.Rising(boolVariableInput);
```

#### `Getting another value from Function`

##### `Output State`
```C
boolReturnOutput = variableFunction.Output();
```

### Example:

```C
#include "MicroBeaut.h"


#define inputPin 8  // Define Input Pin

MicroBeaut_Rising reFunction; // Rising Edge Variable
bool inputState;    // Input State
bool prevInput;     // Previous Input State
bool outputState;   // Output State

void setup() {
	pinMode(inputPin, INPUT);     // Set Pin as an Input Mode
	pinMode(LED_BUILTIN, OUTPUT); // Set Pin as an Output Mode
}

void loop() {
	prevInput = inputState;                                 // Previous Input = Current Input
	inputState = reFunction.Rising(digitalRead(inputPin));  // Read Input and Rising Edge Detector
	outputState ^= (inputState & !prevInput);               // Toggle Output
	digitalWrite(LED_BUILTIN, outputState);                 // Write Output
}
```

## Falling (Falling Edge)

Set Output on the falling edge of Input.

### `Syntax:`

#### `Declaration`
```C
MicroBeaut_Falling variableFunction;
```
#### `Function Use`

```C
boolReturnValue = variableFunction.Falling(boolVariableInput);
```

#### `Getting another value from Function`

##### `Output State`
```C
boolReturnOutput = variableFunction.Output();
```

### Example:

```C
#include "MicroBeaut.h"


#define inputPin 8  // Define Input Pin

MicroBeaut_Falling feFunction;  // Falling Edge Variable
bool inputState;    // Input State
bool prevInput;     // Previous Input State
bool outputState;   // Output State

void setup() {
	pinMode(inputPin, INPUT);     // Set Pin as an Input Mode
	pinMode(LED_BUILTIN, OUTPUT); // Set Pin as an Output Mode
}

void loop() {
	prevInput = inputState;                    // Previous Input = Current Input
	inputState = feFunction.Falling(digitalRead(inputPin)); // Read Input and Falling Edge Detector
	outputState ^= (inputState & !prevInput);  // Toggle Output
	digitalWrite(LED_BUILTIN, outputState);    // Write Output
}
```

---

# Schedule

##  TimeSchedule (Schedule execution at specified time intervals)

The TimeSchedule function is used to schedule a selected subroutine's execution after the specified period of time has passed and the output is TRUE for one scan. Otherwise, the output is FALSE. Input enables the function.

### `Syntax:`

#### `Declaration`
```C
MicroBeaut_TimeSchedule variableFunction;
```
#### `Function Use`

```C
variableFunction.Config(floatTimeScheduleInSecond, CallbackFunction);
boolReturnValue = variableFunction.Run(boolVariableEnable = true);
```

### Example:

```C
#include "MicroBeaut.h"


#define inputPin 8  // Define Input Pin

MicroBeaut_TimeSchedule tsFunction; // Time Schedule Variable
bool enableState;    // Input State
bool outputState;   // Output State

const float timeSchedule = 1.0; // Time Schedule = 1 Second

void setup() {
	pinMode(inputPin, INPUT_PULLUP);  // Set Pin as an Input Mode
	pinMode(LED_BUILTIN, OUTPUT);     // Set Pin as an Output Mode
	tsFunction.Config(timeSchedule, ToggleStateRoutine);  // Set Time Schedule and Callback Function
}

void loop() {
	enableState = digitalRead(inputPin);     // Read Input
	tsFunction.Run(enableState);             // Time Schedule Function with Enable
	digitalWrite(LED_BUILTIN, outputState); // Write Output
}

void ToggleStateRoutine() {
	outputState = !outputState;
}
```

##  ScanSchedule (Schedules execution after a certain number of scans)

The ScanSchedule function is used to schedule a selected subroutine's execution after a specified number of scans occur. Input enables the function. Output is TRUE after the specified number of scans occur and holds TRUE for one scan.

### `Syntax:`

#### `Declaration`
  ```C
  MicroBeaut_ScanSchedule variableFunction;
```
#### `Function Use`

```C
variableFunction.Config(uIntNumberOfScan, CallbackFunction);
boolReturnValue = variableFunction.Run(boolVariableEnable);
```

#### `Getting other values from Function`

##### `Output State`
```C
boolReturnOutput = variableFunction.Output();
```
##### `Actual Time`
```C
floatReturnActualTimeInSecond = variableFunction.Actual();
```


### Example:

```C
#include "MicroBeaut.h"


#define inputPin 8  // Define Input Pin

MicroBeaut_ScanSchedule ssFunction; // Scan Schedule Variable
bool enableState;   // Enable State
bool outputState;   // Output State

const unsigned long numberOfScan = 17450; // Number of scans

void setup() {
  pinMode(inputPin, INPUT_PULLUP);    // Set Pin as an Input Mode
  pinMode(LED_BUILTIN, OUTPUT);       // Set Pin as an Output Mode
  ssFunction.Config(numberOfScan, ToggleStateRoutine);  // Set Scan Schedule and Callback Function
}

void loop() {
  enableState = digitalRead(inputPin);     // Read Input
  ssFunction.Run(enableState);             // Scan Schedule Function with Enable
  digitalWrite(LED_BUILTIN, outputState); // Write Output
}

void ToggleStateRoutine() {
  outputState = !outputState;
}
```

----
## Reference
[Triconex TriStation™ 1131 Developer’s Workbench Libraries](https://www.se.com/ww/en/work/products/industrial-automation-control/triconex-safety-systems/)
