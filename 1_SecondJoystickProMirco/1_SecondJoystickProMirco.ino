/*
* Elite 6 axis of freedom joystick
* v1.0 - Arduino Pro Micro as Second joystick
* 
* - Prerequisite: https://github.com/MHeironimus/ArduinoJoystickLibrary/tree/version-2.0
* 
*/

#include "Joystick.h"

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_JOYSTICK, 4, 0,
  true, true, false, // X, Y axis
  false, false, false,
  false, false, false, false, false);

#define joy1X A0
#define joy1Y A1
#define joy2X A2
#define joy2Y A3

#define RXLED 17

void setup() {
  Joystick.setXAxisRange(-127, 127);
  Joystick.setYAxisRange(-127, 127);
  Joystick.setZAxisRange(-127, 127);
  Joystick.setRxAxisRange(-127, 127);
 
  Joystick.begin(false);

  pinMode(RXLED, OUTPUT);
  TXLED0;
}

void loop() {
  signed long mapped;

  digitalWrite(RXLED, HIGH);

  int x1Value = analogRead(joy1X); // Joystick X axis
  int y1Value = analogRead(joy1Y); // Button 0, 1
  int x2Value = analogRead(joy2X); // Button 2, 3
  int y2Value = analogRead(joy2Y); // Joystick Y axis

  mapped = map(x1Value, 180, 823, 127, -127);
  Joystick.setXAxis(mapped);
  mapped = map(y2Value, 180, 750, 127, -127);
  Joystick.setYAxis(mapped);

  Joystick.setButton(0, y1Value < 300);
  Joystick.setButton(1, y1Value > 600);

  Joystick.setButton(2, x2Value > 800);
  Joystick.setButton(3, x2Value < 200);

  Joystick.sendState();

  delay(5);
  digitalWrite(RXLED, LOW);
  delay(5);
}

