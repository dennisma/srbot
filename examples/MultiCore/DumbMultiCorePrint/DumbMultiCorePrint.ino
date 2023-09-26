void setup() {
  Serial.begin(115200);
  while(!Serial);
  //Serial.println("Setup 0");


}

void loop() {
  for (int i=0;i<5;i++)
    Serial.println("core:0");
  delay(750);

}


void setup1() {
  while(!Serial);
  //Serial.println("\t\tSetup 1");

}

void loop1() {
  for (int i=0;i<5;i++)
    Serial.println("core:1");
  delay(750);
}