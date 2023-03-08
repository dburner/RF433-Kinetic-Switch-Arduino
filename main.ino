#include <Arduino.h>
#include <avr/sleep.h>
#include "pulse.h"

// Define pins
const int switchPin = 3;

void myFunction() {
  // Read the value of the switch
  int switchState = digitalRead(switchPin);

  send_commmand();
}

void setup() {
  // Initialize switch pin
  pinMode(switchPin, INPUT_PULLUP);

  // Configure interrupt for switch pin
  attachInterrupt(digitalPinToInterrupt(switchPin), myFunction, CHANGE);

  // Configure sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Serial.println("Entering sleep from loop command");
  sleep_bod_disable();

  // send_commmand();
  // delay(3000);
}