#pragma once
#include "Adafruit_CCS811.h"
#include "MessageProducer.h"

class AirQualitySensor : public CleanAIR::MessageProducer {
 public:
  AirQualitySensor();
  virtual void Loop() override;

 private:
  Adafruit_CCS811 sensor;
  CleanAIR::MessageJson CreateMessage(const int eCO2, const int tVOC);
};