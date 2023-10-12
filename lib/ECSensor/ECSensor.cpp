#include "ECSensor.h"

ECSensor::ECSensor(const char *id, Stream &Serial_port) {
  sensor_id = id;
  static Ezo_uart Module(Serial_port);
  module = &Module;
}

void ECSensor::getReading() {
  module->send_read();
  ec = module->get_reading();
}
