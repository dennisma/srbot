#include "RobotSetup.hpp"

using namespace srbots;

OLEDDisplay oled(port0);
#define DebugPrint(s) Serial.println(s)

void TestAnimateOLEDLine()
{
 // OLEDDisplay oled(mux(0));
  if (oled.init() == false)
    DebugPrint("Oled failed to initialize");

  bool forward = true;
  int y0 = 0, y1 = 60;
  while (1)
  {
    oled.clear();
    oled.drawLine(0, y0, 128, y1);
    oled.updateDisplay();
    if (!y1)
      forward = false;
    else if (!y0)
      forward = true;
    y0 = (forward) ? y0 + 1 : y0 - 1;
    y1 = (forward) ? y1 - 1 : y1 + 1;
  }
}

void setup() {
  RobotSetup();
  Serial.begin(9600);
  Serial.println("yo");

  TestAnimateOLEDLine();
}

void loop() {
    Serial.println("yo");

}
