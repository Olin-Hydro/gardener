#pragma once
#include "ph_grav.h"

/**
 * Implement a class to handle the pH sensor.
 *
 * Create a pH sensor with a given id, pin, and pH value.
 * Update the pH value by performing readings.
 */
class pHSensor {
public:
  // String representing the sensor id in the database.
  const char *sensor_id;
  // Float representing the pH value read from the sensor.
  float pH;
  // uint8_t representing the analog pin to which the sensor is corrected.
  uint8_t pin;

  /**
   * Create an instance of pHSensor.
   *
   * Given an id and a pin, assign these values to their respective
   * instance values of the class.
   *
   * @param id String representing the sensor id in the database.
   * @param analogPin uint8_t representing the analog pin to which the sensor is
   * connected.
   */
  pHSensor(const char *id, uint8_t analogPin);

  /**
   * Perform a reading of the pH sensor.
   *
   * Get a reading from the sensor and store the value obtained in pH.
   */
  void getReading();
};
