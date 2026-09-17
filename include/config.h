#pragma once

#include <stdint.h>

constexpr unsigned long SERIAL_BAUD = 9600;

// PWM duty, 0..255.
constexpr uint8_t SPEED_FORWARD = 200;
constexpr uint8_t SPEED_BACKWARD = 150;
constexpr uint8_t SPEED_TURN = 150;

// Photoresistor reading (0..1023) above which a side counts as lit.
constexpr int LIGHT_THRESHOLD = 500;

// Obstacle avoidance. The robot stops and looks around when something is closer than
// OBSTACLE_DISTANCE_CM. If both sides are closer than DEAD_END_DISTANCE_CM it turns around.
constexpr long OBSTACLE_DISTANCE_CM = 25;
constexpr long DEAD_END_DISTANCE_CM = 10;
constexpr long LED_WARNING_DISTANCE_CM = 30;

// Servo angles for the sonar. The servo does not reach a clean 0 and 180.
constexpr uint8_t SERVO_CENTER = 90;
constexpr uint8_t SERVO_LEFT = 5;
constexpr uint8_t SERVO_RIGHT = 177;
