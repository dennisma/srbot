#include "RobotSetup.hpp"

using namespace srbots;

OLEDDisplay oled(port0);
#define DebugPrint(s) Serial.println(s)

void TestAnimateOLEDRectangles()
{
 // OLEDDisplay oled(mux(0));
  if (oled.init() == false)
    DebugPrint("Oled failed to initialize");

  int x = 0;
  bool forward = true;
  while (1)
  {
    oled.clear();
    x = (forward) ? x + 1 : x - 1;
    if (x == 0)
    {
      forward = true;
    }
    else if (x == 128 - 30)
    {
      forward = false;
    }
    oled.drawRect(x, 0, 30, 40);
    oled.updateDisplay();
  }
}

void setup() {
  RobotSetup();
  Serial.begin(9600);
  Serial.println("yo");

  TestAnimateOLEDRectangles();
}

void loop() {
    Serial.println("yo");

}
