#include <Arduino.h>
#include "pulse.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  Serial.println("Sending command");
  send_commmand();

  Serial.println("delay");
  delay(3000);
}
