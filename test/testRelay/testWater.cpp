#include "relay.h"
#include <Arduino.h>
#include <unity.h>

// Create an instance of relay for the water pump
Relay relay(A2, "water");

/**
 * Test that the relay is turned on when it should be.
 */
void testOn() {
  relay.on();
  TEST_ASSERT_EQUAL(HIGH, digitalRead(relay.pin));
}

/**
 * Test that the relay is turned off when it should be.
 */
void testOff() {
  relay.off();
  TEST_ASSERT_EQUAL(LOW, digitalRead(relay.pin));
}

void setup() {
  // run the tests
  UNITY_BEGIN();
  RUN_TEST(testOn);
  RUN_TEST(testOff);
  UNITY_END();
}

void loop() {}
