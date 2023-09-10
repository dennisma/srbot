#include "RobotSetup.hpp"

using namespace srbots;

#define DebugPrint(s) Serial.println(s)

ColorDetector color(port0);

void setup() {
  RobotSetup();
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("Starting...");

  delay(1000);

}
void loop(){
  Serial.println("__________________________");
  Serial.print("port0\tSDA:");
  Serial.print(port0->sda_pin());
  Serial.print("\tSCL:");
  Serial.println(port0->scl_pin());
  port0->scan();
   
  Serial.print("port1\tSDA:");
  Serial.print(port1->sda_pin());
  Serial.print("\tSCL:");
  Serial.println(port1->scl_pin());
  port1->scan();

  Serial.println("done");
  delay(5000);
}
