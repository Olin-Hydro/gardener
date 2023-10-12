#include "executor.h"
#include "ECSensor.h"
#include "pHSensor.h"
#include <ArduinoJson.h>
#include <string.h>

// function to parse through JSON object and get all of the fields
void parse(JsonObject item, parsed_commands *new_command) {
  const char *ref_id = item["ref_id"];
  const char *id = item["_id"];
  const char *type = item["type"];
  int time = item["cmd"];
  new_command->ref_id = ref_id;
  new_command->id = id;
  new_command->type = type;
  new_command->time = time;
  if (strcmp((char *)new_command->type, "sensor") == 0) {
    new_command->is_sensor = 1;
  } else {
    new_command->is_sensor = 0;
  }
}

int execute_sensor(parsed_commands *cmd, ECSensor *EC, pHSensor *pH) {
  if ((cmd->ref_id[0] == EC->sensor_id[0]) == 1) {
    Serial.println("its an EC sensor");
    EC->getReading();
    cmd->val = EC->ec;
  }
  if ((cmd->ref_id[0] == pH->sensor_id[0]) == 1) {
    Serial.println("The command is to take a pH reading.");
    pH->getReading();
    cmd->val = pH->pH;
    Serial.print("The current pH is:  ");
    Serial.println(pH->pH);
  }
  return 0;
}

int execute_relay(parsed_commands *cmd, Relay *water, Relay *light) {
  if ((cmd->ref_id[0] == water->id[0]) == 1) {
    // water->perform_task((int)cmd->time);
    Serial.printf("Water turned on for %d seconds \n", cmd->time);
  }
  if ((cmd->ref_id[0] == light->id[0]) == 1) {
    light->perform_task((int)cmd->time);
  }
  return 0;
}
