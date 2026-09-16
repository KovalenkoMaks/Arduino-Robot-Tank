#pragma once

#include <Arduino.h>

// HC-SR04 ultrasonic distance sensor.
class Sonar {
public:
  // Returned when nothing echoes back within range.
  static constexpr long NO_ECHO_CM = 999;

  struct Pins {
    uint8_t trig;
    uint8_t echo;
  };

  explicit constexpr Sonar(const Pins& pins) : pins_(pins) {}

  void begin() const;

  // Blocks while waiting for the echo, 25 ms at most.
  long readCm() const;

private:
  Pins pins_;
};
