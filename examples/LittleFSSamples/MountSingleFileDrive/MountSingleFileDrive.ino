#include <LittleFS.h>
#include <SingleFileDrive.h>

void myPlugCB(uint32_t data) {
    // Tell my app not to write to flash, we're connected
}

void myUnplugCB(uint32_t data) {
    // I can start writing to flash again
}

void myDeleteCB(uint32_t data) {
    // Maybe LittleFS.remove("myfile.txt")?  or do nothing
}

void setup() {
    LittleFS.begin();
    singleFileDrive.onPlug(myPlugCB);
    singleFileDrive.onUnplug(myUnplugCB);
    singleFileDrive.onDelete(myDeleteCB);
    singleFileDrive.begin("joe.txt", "joe.txt");
    // ... rest of setup ...
}

void loop() {
    // Take some measurements, delay, etc.

}