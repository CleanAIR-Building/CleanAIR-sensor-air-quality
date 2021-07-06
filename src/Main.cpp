#include "AirQualitySensor.h"
#include "CleanAIRDevice.h"
#include "Definitions.h"
#include "ESP8266WiFi.h"
#include "Wire.h"
#include <Arduino.h>

AirQualitySensor* airQualitySensor;

void setup() {
  Serial.begin(BAUDRATE);
  airQualitySensor = new AirQualitySensor();
  CleanAIR::SetProducer(airQualitySensor);
  CleanAIR::LoadConfiguration(CONFIG_FILE);
  CleanAIR::ConnectToWifi();
  CleanAIR::ConnectToMQTT();
  CleanAIR::InitializeHeartBeat(HEARTBEAT);
}

void loop() { CleanAIR::Loop(); }