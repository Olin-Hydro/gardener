#include "request.h"

Request::Request() {
  client = std::make_unique<BearSSL::WiFiClientSecure>();

  // turn off SSL certificate validation
  client->setInsecure();

  // use http 10 to properly parse the json later on
  http.useHTTP10(true);
}

void Request::get_command(ECSensor *EC, pHSensor *pH, Relay *water,
                          Relay *light) {
  // initialize our request to the server
  http.begin(*client, cmd_server);

  // pass on our authorization token
  http.addHeader("x-api-key", api_key);

  // Send HTTP GET request
  int ResponseCode = http.GET();

  // print the response code, 200 means a success
  Serial.println(ResponseCode);

  if (ResponseCode > 199 &&
      ResponseCode < 300) { // make sure the response is proper
    // parse the server response
    DynamicJsonDocument doc(
        16384); // calculate docsize
                // https://arduinojson.org/v6/assistant/#/step1
    DeserializationError error = deserializeJson(doc, http.getStream());

    // if testing, uncomment these lines:
    // if (error) {
    //   Serial.print(F("deserializeJson() failed: "));
    //   Serial.println(error.f_str());
    //   return;
    // }

    // if testing, uncomment these lines:
    // if (error) {
    //   Serial.print(F("deserializeJson() failed: "));
    //   Serial.println(error.f_str());
    //   return;
    // }

    for (JsonObject item : doc.as<JsonArray>()) {
      parsed_commands new_cmd;
      parse(item, &new_cmd);
      if (new_cmd.is_sensor == 1) {
        execute_sensor(&new_cmd, EC, pH);
        post_reading(&new_cmd);
        Serial.println("Posted sensor reading.");
      } else {
        execute_relay(&new_cmd, water, light);
      }
      update_cmd_status(&new_cmd);
      Serial.println("Marked command as done.");
    }
  }
}

void Request::post_reading(parsed_commands *cmd) {
  http.begin(*client, reading_server);
  // pass on our authorization token and specify json data
  http.addHeader("x-api-key", api_key);
  http.addHeader("Content-Type", "application/json");

  // create the json document to be sent
  DynamicJsonDocument doc(1024);
  doc["sensor_id"] = cmd->ref_id;
  doc["value"] = cmd->val;
  // serialize json
  serializeJson(doc, http.getStream());

  // post the json
  int httpResponseCode = http.sendRequest("POST", http.getStreamPtr());

  // if testing, uncomment these lines:
  // if (httpResponseCode == -1) {
  //   Serial.println("post request failed");
  //   return;
  // }

  // clear the memory
  doc.clear();
  // end the http request
  http.end();
}

void Request::update_cmd_status(parsed_commands *cmd) {
  // create the request url by combining the base cmd_server and
  // the specific cmd id
  char url[strlen(cmd_server) + strlen(cmd->id)];
  strcpy(url, cmd_server);
  strcat(url, cmd->id);

  http.begin(*client, url);
  // pass on our authorization token and specifiy json data
  http.addHeader("x-api-key", api_key);
  http.addHeader("Content-Type", "application/json");

  // create the json document to be sent
  DynamicJsonDocument doc(1024);
  doc["executed"] = true;
  // serialize json
  serializeJson(doc, http.getStream());

  // send the json as a PULL request
  int httpResponseCode = http.sendRequest("PUT", http.getStreamPtr());

  // if testing, uncomment these lines:
  // if (httpResponseCode == -1) {
  //   Serial.println("put request failed");
  //   return;
  // }

  // clear the memory
  doc.clear();
  // end the http requests
  http.end();
}
