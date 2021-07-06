#include "AirQualitySensor.h"
#include "Arduino.h"
#include "ArduinoJson.h"
#include "CleanAIRDevice.h"

AirQualitySensor::AirQualitySensor() : sensor() {
  Serial.println("Starting Sensor setup now...");
  if (sensor.begin()) {
    while (!sensor.available()) {
      delay(1000);
    }
    sensor.setDriveMode(CCS811_DRIVE_MODE_1SEC);
    Serial.println("CSS811 successfully set up!");
  } else {
    Serial.println("Failed to start sensor!");
    while (1) {
    }
  }
}

void AirQualitySensor::Loop() {
  boolean data_available = sensor.available();
  if (data_available) {
    boolean error_reading_data = sensor.readData();
    if (!error_reading_data) {
      // measure: equivalent CO2, unit: ppm, range: 400-... high
      int eCO2 = sensor.geteCO2();
      // measure: total volatile organic compound, unit: ppb
      // range: 0-... high
      int tVOC = sensor.getTVOC();
      Serial.println("Sensor data read sucessfully!");
      Publish(CleanAIR::GetConfig().mqttTopic.c_str(), CreateMessage(eCO2, tVOC));
    } else {
      Serial.println("Sensor data read failed");
    }
  } else {
    Serial.println("No data available.");
  }
  delay(2000);
}

CleanAIR::MessageJson AirQualitySensor::CreateMessage(const int eCO2, const int tVOC){
  CleanAIR::MessageJson message;
  message["sensor"] = CleanAIR::GetConfig().mqttClientName.c_str();
  message["eCO2"] = eCO2;
  message["TVOC"] = tVOC;
  return message;
}