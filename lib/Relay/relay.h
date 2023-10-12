#include <Arduino.h>

/**
 * Implement a Relay class that handles actuators.
 *
 * Implement a class that turns on an actuator for a
 * specified length of time.
 */
class Relay {
private:
  // The digital pin number to which the relay is connected
  int pin;

public:
  /**
   * Constructor for a relay.
   *
   * Assigns the pin and id values to the instance variables.
   *
   * @param pin Integer representing the digital pin number.
   * @param id String of the id of the actuator in the database.
   */
  Relay(int pin, const char *id);

  // String of the id of the actuator in the database.
  const char *id;

  // Variable to keep track of the current time for determining how long to keep
  // the actuator on.
  unsigned long current_time = 0;

  /**
   * Method to turn the actuator on.
   */
  void on();

  /**
   * Method to turn the actuator off.
   */
  void off();

  /**
   * Method to turn the actuator on for the specified time.
   *
   * @param on_time Integer representing the length of time
   * the realy should be on.
   */
  void perform_task(int on_time);
};
