#include "RobotSetup.hpp"

using namespace srbots;

void setup() {
  RobotSetup();
}

void loop() {
  if (button20.pressed()){
    Serial.println("Pressed 20!!!");
  }
  if (button21.pressed()){
    Serial.println("Pressed 21!!!");
  }
  delay(3000);
}
