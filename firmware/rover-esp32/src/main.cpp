#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "Duras";
const char* password = "debasterot1866";

#define TRIG_PIN 12
#define ECHO_PIN 14
#define LED_PIN 26

void setup()
{
    Serial.begin(115200);
    delay(1000);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

    Serial.println("Connecting to Wi-Fi...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    int attempts = 0;

    while (WiFi.status() != WL_CONNECTED && attempts < 30)
    {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("\nWi-Fi connected!");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    }
    else
    {
        Serial.println("\nWi-Fi connection failed.");
    }

    Serial.println("HC-SR04 Distance Measurement");
}

void loop()
{
    long duration;
    float distance;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    duration = pulseIn(ECHO_PIN, HIGH, 30000);

    distance = duration * 0.0343f / 2.0f;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance > 0 && distance < 20)
    {
    Serial.println("Object detected within 20 cm!");
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("ESP32 online");
    }
    else
    {
        Serial.println("Wi-Fi disconnected");
    }

    delay(500);
}