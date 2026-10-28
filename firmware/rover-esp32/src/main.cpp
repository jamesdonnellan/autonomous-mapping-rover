#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    delay(2000);

    Serial.println("ESP32 Started");
}

void loop() {
    Serial.println("Running...");
    delay(1000);
}
