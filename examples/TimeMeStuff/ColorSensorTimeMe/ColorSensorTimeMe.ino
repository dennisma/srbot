#include "RobotSetup.hpp"

using namespace srbots;

#define DebugPrint(s) Serial.println(s)

ColorDetector color(port0);
TimeMe tm;
void setup() {
  RobotSetup();
  Serial.begin(115200);
  while (!Serial)
    ;

  color.init(5);
    tm.start();
}



void loop() {
  uint16_t r = 0, g = 0, b = 0, c = 0;
  while (!color.colorReady());  
  color.getColors(r, g, b, c);
  tm.stop();
  auto m = tm.milliS();
  tm.start();
  Serial.println(m);
  // Serial.print("blue:");
  // Serial.print(b);
  // Serial.print(",red:");
  // Serial.print(r);
  // Serial.print(",green:");
  // Serial.print(g);
  // Serial.print(",clear:");
  // Serial.println(c);

  // delay(5);
}
