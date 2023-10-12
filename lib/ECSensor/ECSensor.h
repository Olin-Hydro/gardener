#pragma once
#include <Ezo_uart.h>

/**
 * Implement a class for handling an electrical conductivity sensor.
 *
 * Obtain readings from the sensor to determine the nutrient state of
 * the plants.
 */
class ECSensor {
public:
  // String representing the id of the sensor in the database.
  const char *sensor_id;
  // Instance of the Ezo_uart class.
  Ezo_uart *module;
  // Float representing the electrical conductivity value.
  float ec;

  /**
   * Constructor for the ECSensor.
   *
   * Sets the id to the input id and specifies the stream for data.
   *
   * @param id String representing the id of the sensor in the database.
   * @param serial_port Pointer to the serial port to which the sensor is
   * conencted.
   */
  ECSensor(const char *id, Stream &Serial_port);

  /**
   * Perform a reading of the EC sensor.
   *
   * Get the current value of electrical conductivity.
   */
  void getReading();
};
