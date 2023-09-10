#include "RobotSetup.hpp"

using namespace srbots;

#define DebugPrint(s) Serial.println(s)

ColorDetector color(port0);

void setup() {
  RobotSetup();
  Serial.begin(115200);
  while (!Serial)
    ;

  color.init(10);
}

void loop() {
  if (color.colorReady()) {
    uint16_t r = 0, g = 0, b = 0, c = 0;
    color.getColors(r, g, b, c);
    Serial.print("blue:");
    Serial.print(b);
    Serial.print(",red:");
    Serial.print(r);
    Serial.print(",green:");
    Serial.print(g);
    Serial.print(",clear:");
    Serial.println(c);
  }
  delay(5);
}
