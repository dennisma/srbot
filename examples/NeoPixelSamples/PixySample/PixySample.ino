#include "RobotSetup.hpp"

using namespace srbots;

enum pixy_color { RED = 0xFF0000,
                  GREEN = 0x00FF00,
                  BLUE = 0x0000FF,
                  BLACK = 0x000000,
                  WHITE = 0xFFFFFF };

void setup() {
  RobotSetup();
  Serial.begin(115200);
}

void loop() {
  pixy.fill(RED);       // both pixys will be red
  pixy.show();          // must call show after setting -this is when it displays
  delay(1000);
  pixy.fill(BLUE);      // both pixys will be blue
  pixy.show();
  delay(1000);
  pixy.fill(GREEN);     // both pixys will be green
  pixy.show();
  delay(1000);
  pixy.fill(WHITE);     // both pixys will be WHITE
  pixy.show();
  delay(1000);



  for (int i = 0; i < 25; i++) {    // this will flash blue and red like a police car
    pixy.setPixelColor(0, BLUE);    // set first to blue
    pixy.setPixelColor(1, RED);     // set second to read
    pixy.show();
    delay(100);
    pixy.setPixelColor(0, RED);     // set first to red
    pixy.setPixelColor(1, BLUE);    // set second to blue
    pixy.show();
    delay(100);
  }
  pixy.clear();                     // clear turns them off 
  pixy.show();  
  delay(2000);
}
