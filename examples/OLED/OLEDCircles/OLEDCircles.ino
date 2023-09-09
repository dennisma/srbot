#include "RobotSetup.hpp"

using namespace srbots;
OLEDDisplay oled(port0);

#define DebugPrint(s) Serial.println(s)
void TestCircle()
{
  DebugPrint("\nStarting...circe");
  delay(2000);

  ////OLEDDisplay oled(mux(0));
  if (oled.init() == false)
    DebugPrint("Oled failed to initialize");

  int rad = 2;
  bool forward = true;
  while (1)
  {
    oled.clear();

    oled.drawCircle(40, 60, rad); // ok
    oled.drawCircle(20, 10, rad);
    oled.drawCircle(80, 30, rad);
    oled.drawCircle(120, 15, rad);

    oled.updateDisplay();
    if (rad > 20)
      forward = false;
    else if (rad <= 0)
      forward = true;

    rad = (forward) ? rad + 2 : rad - 2;
  }
}

void setup() {
  RobotSetup();
  Serial.begin(9600);
  Serial.println("yo");

  TestCircle();
}

void loop() {
    Serial.println("yo");

}
