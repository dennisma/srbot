#include "RobotSetup.hpp"

using namespace srbots;

Button botton20(20);

void setup() {
  botton20.init();
}

void loop() {
  if (botton20.pressed()){
    Serial.println("Pressed!!!");
  }
  delay(3000);
}
