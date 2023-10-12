#include "pHSensor.h"
#include <unity.h>


// Create an instance of EC sensor
ECSensor sensor("pH", A0);

void testgetReading() {
  sensor.getReading();
  Serial.println(sensor.ec);
  TEST_ASSERT(sensor.pH > 0.0 && phSensor.pH < 15);
}

