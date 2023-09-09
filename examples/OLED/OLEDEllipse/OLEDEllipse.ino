#include "RobotSetup.hpp"

using namespace srbots;

OLEDDisplay oled(port0);
#define DebugPrint(s) Serial.println(s)

void TestEllipse()
{
  //OLEDDisplay oled(mux(0));
  if (oled.init() == false)
    DebugPrint("Oled failed to initialize");

  int x0 = 5;
  int y0 = 5;
  int x1 = x0 + 90;
  int y1 = 60;

  bool forward = true;
  while (1)
  {
    oled.clear();

    oled.drawRect(x0, y0, x1, y1);
    oled.fillEllipse(x0, y0, x1, y1);
    oled.updateDisplay();

    if (x1 > 120)
      forward = false;
    else if (x1 <= x0 + 1)
      forward = true;

    x1 = (forward) ? x1 + 1 : x1 - 1;
  }
}



void setup() {
  RobotSetup();
  Serial.begin(9600);
  Serial.println("yo");

  TestEllipse();
}

void loop() {
    Serial.println("yo");

}
