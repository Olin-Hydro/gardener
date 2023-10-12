#include "pHSensor.h"

pHSensor::pHSensor(const char *id, uint8_t analogPin) {
  sensor_id = id;
  pin = analogPin;
}

void pHSensor::getReading() {
  // use Gravity_pH to read the pH value
  Gravity_pH grav_ph = pin;
  pH = grav_ph.read_ph();
}
