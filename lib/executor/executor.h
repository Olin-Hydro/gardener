#pragma once
#include "ECSensor.h"
#include "pHSensor.h"
#include "relay.h"
#include <ArduinoJson.h>
#include <string.h>

/**
 * Struct to store the commands after parsing the json.
 */
struct parsed_commands {
  // Strng representing the id of indiviual part
  const char *ref_id;
  // String representing the id of command
  const char *id;
  // String reprenting the type of command
  const char *type;
  // Boolean representing where it is a sensor
  bool is_sensor;
  // Float represeting the sensor reading
  float val;
  // actuator timing
  int time;
};

/**
 * Parse the json object into a parsed_commands struct.
 *
 * Given a jsonobject, parse the json and store each value into
 * the respective field in a parsed_commands struct.
 *
 * @param item JsonObject obtained from the database.
 * @param new_command Pointer to a parsed_commands struct in which the
 * values in item will be stored.
 */
void parse(JsonObject item, parsed_commands *new_command);

/**
 * Perform a sensor reading.
 *
 * Given a command and the instances of each sensor,
 * determine which sensor should be used and then perform the reading
 * and store the value in the parsed_commands val field. Return 0
 * if successful.
 *
 * @param cmd Pointer to a parsed_commands struct of the command.
 * @param EC Pointer to an instance of ECSensor.
 * @param pH Pointer to an instance of pHSensor.
 *
 * @return 0 if successful.
 */
int execute_sensor(parsed_commands *cmd, ECSensor *EC, pHSensor *pH);

/**
 * Perform a relay command.
 *
 * Given a command and the instances of each relay,
 * determine which relay should be used and then turn that relay on
 * for the specified length of time.
 *
 * @param cmd Pointer to a parsed_commands struct of the command.
 * @param water Pointer to an instance of Relay representing the water pump.
 * @param light Pointer to an instance of Relay representing the light.
 *
 * @return 0 if successful.
 */
int execute_relay(parsed_commands *cmd, Relay *water, Relay *light);
