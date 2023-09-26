#include "myutil.hpp"

using namespace srbots;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  TimeMe tm(true);

  // tm.start();
  delayMicroseconds(1000);
  // tm.stop();
  // auto end = tm.milliS();

  // tm.printVals();
}

void loop() {
  TimeMe tm(true);
  delay(1);
}
