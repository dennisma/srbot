#include "RobotSetup.hpp"
using namespace srbots;

void setup() {
  RobotSetup();
  Serial.begin(115200);
  while (!Serial)
    ;
  enc.reset();
}

void loop() {
  static auto old_enc = enc.count();
  if (old_enc != enc.count()){
    old_enc = enc.count();
    Serial.println(enc.count());
  }
}
