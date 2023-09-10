#include "RobotSetup.hpp"

using namespace srbots;

#define DebugPrint(s) Serial.println(s)

ColorDetector color(port0);
OLEDDisplay oled(port0);

void setup() {
  RobotSetup();
  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println("yo");

  if (oled.init() == false)
    DebugPrint("Oled failed to initialize");

  color.init(30);

  Serial.println("Ready to enter Loop");

}

void loop() {
  using namespace std;
  int i=0;
  static std::string s;
  if (color.colorReady()) {
    uint16_t r = 0, g = 0, b = 0, c = 0;
    color.getColors(r, g, b, c);

    oled.clear();
    s = "R: " + to_string(r);
    oled.drawtext(i++, s);
    s = "G: " + to_string(g);
    oled.drawtext(i++, s);
    s = "B: " + to_string(b);
    oled.drawtext(i++, s);
    s = "C: " + to_string(c);
    oled.drawtext(i++, s);
    oled.updateDisplay();

    // Serial.print("red: ");
    // Serial.print(r);

    // Serial.print(" green: ");
    // Serial.print(g);

    // Serial.print(" blue: ");
    // Serial.print(b);

    // Serial.print(" clear: ");
    // Serial.println(c);
  }
  //delay(5);
}
