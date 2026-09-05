#pragma once

#include <Arduino.h>

// Keyestudio tank robot on an Arduino Uno.

constexpr uint8_t PIN_MOTOR_LEFT_DIR = 13;
constexpr uint8_t PIN_MOTOR_LEFT_PWM = 11;
constexpr uint8_t PIN_MOTOR_RIGHT_DIR = 12;
constexpr uint8_t PIN_MOTOR_RIGHT_PWM = 3;

constexpr uint8_t PIN_IR_RECEIVER = A0;

constexpr uint8_t PIN_LIGHT_LEFT = A1;
constexpr uint8_t PIN_LIGHT_RIGHT = A2;

constexpr uint8_t PIN_MATRIX_SDA = A4;
constexpr uint8_t PIN_MATRIX_SCL = A5;

constexpr uint8_t PIN_SONAR_ECHO = 4;
constexpr uint8_t PIN_SONAR_TRIG = 5;
constexpr uint8_t PIN_SERVO = 9;

// The servo takes over Timer1, so there is no PWM on pin 10: on/off only.
constexpr uint8_t PIN_LED = 10;
