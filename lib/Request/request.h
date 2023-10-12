#include <Arduino.h>
// #include "ArduinoJson.h" // if the library is in lib
#include "ECSensor.h"
#include "executor.h"
#include "pHSensor.h"
#include "secrets.h"
#include <ArduinoJson.h> // if the library is added through platform io
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecureBearSSL.h>
#include <string.h>

/**
 * Implement a request class to handle server communication.
 *
 * A request class that communciates with the server to
 * GET new commands, POST sensor readings, and PUT the
 * updated command status.
 */
class Request {
private:
  // key value for the api requests
  const char *api_key = SECRET_VALUE;
  // url for requests assocated with commands
  const char *cmd_server = "https://hydrangea.kaz.farm/cmd/";
  // url for requests associated with readings
  const char *reading_server = "https://hydrangea.kaz.farm/sensors/logging/";

  // create a secure client in order to connect to https
  // more info: https://randomnerdtutorials.com/esp8266-nodemcu-https-requests/
  std::unique_ptr<BearSSL::WiFiClientSecure> client;
  // instance of http class
  HTTPClient http;

public:
  /**
   * Constuctor for the class.
   *
   * Sets the client to insecure and specifies use of http10.
   */
  Request();

  /**
   * Get the latest command from the database.
   *
   * Send a http get request to the cmd_server and store the result
   * in a json. Parse the json and perform the command. If the command
   * targets a sensor, perform the reading and call post_reading.
   * If the command targets a relay, perform the command.
   * Update the command status using update_cmd_status.
   *
   * @param EC Pointer to an instance of the ECSensor class.
   * @param pH Pointer to an instance of the pHSensor class.
   * @param water Pointer to an instance of the Relay class used for the water
   * pump.
   * @param light Pointer to an instance of the Relay class used for the light.
   */
  void get_command(ECSensor *EC, pHSensor *pH, Relay *water, Relay *light);

  /**
   * Post sensor value to the database.
   *
   * Send an http post request of the sensor id and its latest reading
   * to the reading_server.
   *
   * @param cmd Pointer to the command, which contains the sensor id and latest
   * value
   */
  void post_reading(parsed_commands *cmd);

  /**
   * Update command status in database.
   *
   * After the command has been executed, update the command field of the
   * specified command by sending a PUT request to the cmd_server that changes
   * the value of the executed field to true.
   *
   * @param cmd Pointer to the command, which contains the command id
   */
  void update_cmd_status(parsed_commands *cmd);
};
