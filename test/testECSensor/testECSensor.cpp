#include "ECSensor.h"
#include <unity.h>


// Create an instance of EC sensor
ECSensor sensor("EC", Serial);

void testgetReading() {
  sensor.getReading();
  Serial.println(sensor.ec);
  TEST_ASSERT(sensor.EC > -0.01 && sensor.EC < 1500);
}
