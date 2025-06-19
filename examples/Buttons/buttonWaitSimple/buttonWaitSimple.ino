#include "RobotSetup.hpp"

void setup(){
  Serial.begin(115200);
  Serial.println("OK");
}

void loop(){
  Serial.println("Push GP20");
  button20.waitUntilPressed();

  Serial.println("Push GP21");
  button21.waitUntilPressed();
}