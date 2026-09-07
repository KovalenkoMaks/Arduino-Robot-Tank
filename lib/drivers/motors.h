#pragma once

#include <Arduino.h>

// Two tracks, each with a direction pin and a PWM pin.
class Motors {
public:
  struct Pins {
    uint8_t leftDir;
    uint8_t leftPwm;
    uint8_t rightDir;
    uint8_t rightPwm;
  };

  explicit constexpr Motors(const Pins& pins) : pins_(pins) {}

  void begin() const;

  // Speed per track, -255..255. Negative runs the track backward.
  void set(int16_t left, int16_t right) const;
  void stop() const;

private:
  Pins pins_;
};
