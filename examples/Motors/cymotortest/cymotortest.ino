#include "RobotSetup.hpp"
using namespace srbots;

void setup() {
  RobotSetup();
}

int speed=60;

void loop() {
  speed = -speed;
  leftmotor.speed(speed);
  rightmotor.speed(speed);
  delay(3000);
}

