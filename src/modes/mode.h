#pragma once

#include <Arduino.h>

// One behaviour of the robot. Only one mode is active at a time.
class Mode {
public:
  virtual const __FlashStringHelper* name() const = 0;
  // Image shown on the LED matrix while the mode is active (PROGMEM).
  virtual const uint8_t* icon() const = 0;

  virtual void enter() {}
  // Called on every pass of the main loop, so it must not block.
  virtual void update() {}
  virtual void onKey(uint8_t /*key*/) {}
  virtual void exit() {}

protected:
  ~Mode() = default;
};
