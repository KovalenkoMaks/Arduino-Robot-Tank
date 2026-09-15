#pragma once

#include <Arduino.h>

class Led {
public:
  explicit constexpr Led(uint8_t pin) : pin_(pin) {}

  void begin();
  void set(bool on);
  void toggle();

private:
  uint8_t pin_;
  bool on_ = false;
};
