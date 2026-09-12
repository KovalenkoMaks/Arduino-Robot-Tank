#pragma once

#include <Arduino.h>

// 16x8 LED matrix on a two-wire bus. An image is one byte per column, bit 0 is the top row.
class LedMatrix {
public:
  static constexpr uint8_t COLUMNS = 16;

  struct Pins {
    uint8_t scl;
    uint8_t sda;
  };

  explicit constexpr LedMatrix(const Pins& pins) : pins_(pins) {}

  void begin() const;

  // The image must be stored in flash (PROGMEM).
  void show(const uint8_t* image) const;
  void clear() const;

private:
  void start() const;
  void send(uint8_t data) const;
  void end() const;
  void write(const uint8_t* columns) const;

  Pins pins_;
};
