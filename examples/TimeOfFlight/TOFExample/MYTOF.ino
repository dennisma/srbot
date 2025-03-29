#include "RobotSetup.hpp"

using namespace srbots;

TOF tof(port0);

void setup() {
  RobotSetup();
  Serial.begin(115200);
  // while (!Serial)
  //   ;
  Serial.println("Starting...");
  if (!tof.init()){
    Serial.println("Failed");
    while(true);
  }

  Serial.println("Done Setup");
}

void loop() {

  Serial.print(tof.getDistance());
  Serial.print('\t');
  Serial.println(tof.getDistanceMM());
}
