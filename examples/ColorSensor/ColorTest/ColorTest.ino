#include "RobotSetup.hpp"

using namespace srbots;

#define DebugPrint(s) Serial.println(s)

ColorDetector color(port0);

void setup() {
  RobotSetup();
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println("yo");

  color.init(5);

  Serial.println("Ready to enter Loop");
  while (!Serial.available())
    ;
  while (Serial.available()) 
    Serial.read();
}

void loop() {
  if (color.colorReady()) {
    uint16_t r = 0, g = 0, b = 0, c = 0;
    color.getColors(r, g, b, c);

    Serial.print("red: ");
    Serial.print(r);

    Serial.print(" green: ");
    Serial.print(g);

    Serial.print(" blue: ");
    Serial.print(b);

    Serial.print(" clear: ");
    Serial.println(c);
  }
  delay(5);
}
