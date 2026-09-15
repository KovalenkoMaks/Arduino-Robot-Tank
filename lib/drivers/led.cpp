#include "led.h"

void Led::begin() {
  pinMode(pin_, OUTPUT);
  set(false);
}

void Led::set(bool on) {
  on_ = on;
  digitalWrite(pin_, on ? HIGH : LOW);
}

void Led::toggle() {
  set(!on_);
}
