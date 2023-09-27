#include "RobotSetup.hpp"

using namespace srbots;
OLEDDisplay oled(port0);

void DrawFace() {
  Serial.println("\nStarting...circe");
  delay(2000);

  ////OLEDDisplay oled(mux(0));
  if (oled.init() == false)
    Serial.println("Oled failed to initialize");

  int rad = 5;
  bool forward = true;

  oled.clear();
  oled.fillCircle(128 / 2, 64 / 2, 64/2);
  oled.fillCircle(64-13,32-10, rad, WriteMode::SUBTRACT);
  oled.fillCircle(64+13,32-10, rad, WriteMode::SUBTRACT);
  oled.fillEllipse( 64-13, 32+8, 64+13, 32+15,WriteMode::SUBTRACT);

  oled.updateDisplay();
}

void setup() {
  Serial.begin(115200);
  RobotSetup();
  DrawFace();
}

void loop() {

}
