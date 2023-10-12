#include "relay.h"

Relay::Relay(int pin, const char *id) {
  this->pin = pin;
  this->id = id;
  // set the pinmode as output
  pinMode(this->pin, OUTPUT);
}

void Relay::on(void) { digitalWrite(pin, HIGH); }

void Relay::off(void) { digitalWrite(pin, LOW); }

void Relay::perform_task(int on_time) {
  current_time = millis();
  // for the amount of time specified, turn the relay on
  while (millis() <= (current_time + (unsigned long)(1000 * on_time))) {
    on();
  }
  off();
}
