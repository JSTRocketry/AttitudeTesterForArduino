#include <Arduino.h>

void setup() {
    Serial.begin(11520);
    Serial.println("Hello");
}

void loop() {
    if(Serial.available() > 0){
      Serial.println(Serial.read());
    }
}
