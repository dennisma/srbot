#include "RobotSetup.hpp"

using namespace srbots;
UltraSonic ping;

void setup() {
  RobotSetup();
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Starting");
  ping.init();
}

void loop() {
  int64_t pingdistance;
  ping.get(pingdistance);

  Serial.println(pingdistance);
  delay(100);
}
