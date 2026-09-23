#pragma once

#include "led_matrix.h"

// Blinks "MA" twice and then shows "hi" on the LED matrix, without blocking the main loop.
class Greeting {
public:
  explicit Greeting(const LedMatrix& matrix) : matrix_(matrix) {}

  void start();
  void cancel();
  bool running() const;

  // Returns true once, on the call where the last frame has been shown long enough.
  bool update();

private:
  void showFrame() const;

  const LedMatrix& matrix_;
  bool running_ = false;
  uint8_t frame_ = 0;
  unsigned long frameStartedAt_ = 0;
};
