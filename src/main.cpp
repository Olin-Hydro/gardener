#include "ECSensor.h"
#include "executor.h"
#include "pHSensor.h"
#include "request.h"
#include "secrets.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <string.h>

// wifi
const char *ssid = SECRET_SSID;
const char *password = SECRET_PASS;

// server and header key + value
const char *key = SECRET_KEY;
const char *value = SECRET_VALUE;

// define all sensors and relays
uint8_t pH_pin = A0;
Stream &Serial_port = Serial;
int water_pin = 3;
int light_pin = 4;

// placeholder IDs
const char *pH_id = "5f40db6b-10bb-4808-8a3a-1a81fa9f504a";
const char *EC_id = "84fo48u9-88dk-4893-aj03-fkk3l5kj";
const char *water_id = "ac6b77c6-131d-4919-a61f-2b761cac2dca";
const char *light_id = "jo0irj-59fd-398f-4354-3jdjkslj";

pHSensor pH(pH_id, pH_pin);
ECSensor EC(EC_id, Serial_port);
Relay water(water_pin, water_id);
Relay light(light_pin, light_id);

// Create an instance of request
Request req;

void setup() {
  // Start the Serial communication to send messages to the computer
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  // Connect to the network
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.println(" ...");

  int i = 0;
  // Wait for the Wi-Fi to connect
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(++i);
    Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");
  // Send the IP address of the ESP8266 to the computer
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check WiFi connection status
  if (WiFi.status() == WL_CONNECTED) {
    delay(1000);
    // get new commands from the database
    // this will also perform the command and update
    // command status and reading value
    req.get_command(&EC, &pH, &water, &light);
  }
}
