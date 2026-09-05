#pragma once

#include <stdint.h>

constexpr unsigned long SERIAL_BAUD = 9600;

// PWM duty, 0..255.
constexpr uint8_t SPEED_FORWARD = 200;
constexpr uint8_t SPEED_BACKWARD = 150;
constexpr uint8_t SPEED_TURN = 150;
