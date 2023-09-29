#include "RobotSetup.hpp"
using namespace srbots;

void setup() {
  RobotSetup();
  Serial.begin(115200);
  while (!Serial)
    ;
  enc.reset();
  leftmotor.speed(254);
  delay(400);
}
#define testnum 180
void loop() {

  //if (enc.count() == testnum) enc.reset();
  if (enc.count() % testnum == 0) {
    leftmotor.speed(-254);
    delay(73);
    leftmotor.speed(0);
    delay(900);
    Serial.println(enc.count());
    //enc.reset();
    leftmotor.speed(254);
    delay(100);
  }
}
