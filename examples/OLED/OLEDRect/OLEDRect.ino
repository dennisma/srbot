#include "RobotSetup.hpp"

using namespace srbots;

OLEDDisplay oled(port0);
#define DebugPrint(s) Serial.println(s)

void TestOLEDRectangles()
{
  if (oled.init() == false)
    DebugPrint("Oled failed to initialize");

  oled.clear();
  oled.drawRect(0, 0, 30, 40);
  // oled.drawRect(40,10,50,135);
  oled.fillRect(40, 10, 135, 50);
  oled.updateDisplay();
  while (1)
    ;
}

void setup() {
  RobotSetup();
  Serial.begin(9600);
  Serial.println("yo");

  TestOLEDRectangles();
}

void loop() {
    Serial.println("yo");

}
