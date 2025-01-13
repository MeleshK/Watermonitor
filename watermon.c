#include <ESP8266WiFi.h>

#define FLOW_SENSOR D2  // GPIO4 for flow sensor
#define RELAY_PIN D5    // GPIO14 for ozone generator control
#define OZONE_SENSOR A0 // Analog input for ozone sensor (MQ131)

volatile int pulseCount = 0;
float flowRate = 0.0;
float totalLitres = 0.0;
unsigned long lastTime = 0;
float ozoneLevel = 0.0; // Measured in mg/L

// Flow Meter Interrupt Function
void pulseCounter() {
    pulseCount++;
}

void setup() {
    Serial.begin(115200);
    pinMode(FLOW_SENSOR, INPUT);
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(OZONE_SENSOR, INPUT);
    attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR), pulseCounter, FALLING);
    digitalWrite(RELAY_PIN, LOW); // Ensure ozone generator is OFF at startup
}

void loop() {
    if (millis() - lastTime >= 1000) { // Every second
        detachInterrupt(digitalPinToInterrupt(FLOW_SENSOR));

        flowRate = (pulseCount / 7.5); // Convert pulses to L/min
        totalLitres += (flowRate / 60); // Convert to litres

        ozoneLevel = analogRead(OZONE_SENSOR) * (5.0 / 1023.0) * 2.0; // Convert to mg/L (calibration needed)

        Serial.print("Flow Rate: ");
        Serial.print(flowRate);
        Serial.print(" L/min | Total Water: ");
        Serial.print(totalLitres);
        Serial.println(" L");

        Serial.print("Ozone Level: ");
        Serial.print(ozoneLevel);
        Serial.println(" mg/L");

        if (flowRate > 0 && ozoneLevel < 0.5) {
            digitalWrite(RELAY_PIN, HIGH); // Turn ON ozone generator
            Serial.println("Ozone Generator ON");
        } else {
            digitalWrite(RELAY_PIN, LOW); // Turn OFF ozone generator
            Serial.println("Ozone Generator OFF");
        }

        pulseCount = 0;
        lastTime = millis();
        attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR), pulseCounter, FALLING);
    }
}
