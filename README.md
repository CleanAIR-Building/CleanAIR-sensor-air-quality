# AirQuality Sensor

Sensor in use: Adafruit CCS811

Microcontroller: Node MCU, Esp8266-12 WiFi module

Sensor docs: https://learn.adafruit.com/adafruit-ccs811-air-quality-sensor/arduino-wiring-test

Sensor library docs: https://adafruit.github.io/Adafruit_CCS811/html/class_adafruit___c_c_s811.html

Sensor wiring tutorial with NodeMCU: http://kstobbe.dk/2019/01/28/first-sensor-array/

# Functionality:

The sensor collects data for: 
* eCO2 (equivilant CO2) in ppm
* TVOC (total volatile organic compound) in ppb

It uses the CleanAIRDevice library to connect to wifi and mqtt via external configuration. (See: https://github.com/CleanAIR-Building/CleanAIRDevice)

It sends json messages in the following shape:
```
{
    "sensor": <sensor-name>,
    "eCO2": <int-value>,
    "TVOC": <int-value>
}
```
The messages are sent every two seconds.