#include <RobotSetup.hpp>

void setup() {

}

int speed=60;

void loop() {
  speed = -speed;
  leftmotor.speed(speed);
  rightmotor.speed(speed);
  delay(3000);
}

