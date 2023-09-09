#include <string>
#include "RobotSetup.hpp"

using namespace srbots;

OLEDDisplay oled(port0);
#define DebugPrint(s) Serial.println(s)

void TestOLEDRectangles()
{
  if (oled.init() == false)
    DebugPrint("Oled failed to initialize");

  oled.clear();
  int i=0;
  std::string s = "All work and";
  oled.drawtext(i++, s);
  s = "No play makes";
  oled.drawtext(i++, s);
  s = "Jeremy a dull";
  oled.drawtext(i++, s);
  s = "boy...";
  oled.drawtext(i++, s);
  s = "line 5";
  oled.drawtext(i++, s);
  s = "line 6";
  oled.drawtext(i++, s);
  s = "line 7";
  oled.drawtext(i++, s);
  s = "line 8";
  oled.drawtext(i++, s);
  oled.updateDisplay();
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
