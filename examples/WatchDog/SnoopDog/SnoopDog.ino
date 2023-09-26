#include "RobotSetup.hpp"

using namespace srbots;
WDTimer wd;

void setup() {
  RobotSetup();
  auto reset = wd.init(3000);
  Serial.begin(115200);
  while (!Serial) wd.updateDog();

  if (reset){
    Serial.println("SNoopDog done reset me!!!");
  }
  else{
    Serial.println("SNoopDog did NOT reset me!!!");
  }
}


uint64_t count = 0;
void loop() {
  wd.updateDog();
  Serial.printf("count %d\n", ++count);
  if (count == 10) delay(5000);
  else delay(1000);

}
