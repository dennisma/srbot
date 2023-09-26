#include "LittleFS.h"
#include <SingleFileDrive.h>
/* 
  This program prompts the user to either write or read from a file (/joe.txt) 
  on the PICO filesystem.

  You must goto IDE Menu Options -> Tools -> Flas Size and set the FS to 64mb FIRST

  Upload program
  Open Serial Monitor.  You should See:

  Starting File test... 
  Enter a char:
      W - Write
      R - Read

  Type W and then you are prompted to enter a line of text.  Do so and hit enter (make sure NewLine is set in Serial Monitor).
  It will then reboot and prompt you again for W or R.   Type R this time and you will see your file contents.

  If you want to copy the File to your PC see the MountSingleFileDrive sketch

 */

const char* fname = "/joe.txt";

void writeFile() {
  File f = LittleFS.open(fname, "w");
  if (!f) {
    Serial.println("file open(w) failed");
    while (1)
      ;
    delay(1000);
  }

  while(Serial.available())
      Serial.read();

  Serial.println("Enter a line: ");
  uint8_t c='\0';

  while(true){
    while (Serial.available()){
      c = Serial.read();
      f.write(c);
      Serial.print((char)c);
      if (c == '\n'){ 
        f.close();
        Serial.println("Done Writing");
        return;
      }
    }
  }
}

void readFile() {
  File f = LittleFS.open("/joe.txt", "r");

  if (!f) {
    Serial.println("file open(r) failed");
    while (1)
      ;
    delay(1000);
  }

  while (true){
    auto c = f.read();
    if (c == -1) break;
    Serial.print((char)c);
  }

  f.close();

  Serial.println("Done Reading");
}

void setup() {
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("Starting File test...");
  delay(1000);
  LittleFS.begin();

  char menu_option = 'X';
  while (menu_option != 'W' && menu_option != 'R' ) {
    Serial.println("Enter a char:\n\tW - Write\n\tR - Read");
    while (!Serial.available())
      ;
    menu_option = Serial.read();
  }

  switch (menu_option) {
    case 'W':
      writeFile();
      break;
    case 'R':
      readFile();
      break;
  }

  LittleFS.end();
  Serial.println("Rebooting in 2 seconds");
  delay(2000);
  rp2040.reboot();
}

void loop() {
  // put your main code here, to run repeatedly:
}
