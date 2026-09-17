#include "obstacle_avoid_mode.h"

#include "config.h"
#include "icons.h"

namespace {

constexpr unsigned long MEASURE_INTERVAL_MS = 60;
// Time for the servo to get from the center to the left, and from the left to the right.
constexpr unsigned long LOOK_LEFT_MS = 350;
constexpr unsigned long LOOK_RIGHT_MS = 500;
constexpr unsigned long RECENTER_MS = 250;

}  // namespace

void ObstacleAvoidMode::begin() {
  servo_.attach(servoPin_);
  servo_.write(SERVO_CENTER);
}

const __FlashStringHelper* ObstacleAvoidMode::name() const {
  return F("obstacle avoid");
}

const uint8_t* ObstacleAvoidMode::icon() const {
  return icons::SONAR;
}

void ObstacleAvoidMode::enter() {
  servo_.write(SERVO_CENTER);
  go(State::Recenter);
}

void ObstacleAvoidMode::exit() {
  servo_.write(SERVO_CENTER);
  warningLed_.set(false);
}

void ObstacleAvoidMode::go(State next) {
  state_ = next;
  stateStartedAt_ = millis();
}

void ObstacleAvoidMode::update() {
  const unsigned long now = millis();
  const unsigned long elapsed = now - stateStartedAt_;

  switch (state_) {
    case State::Cruise:
      cruise(now);
      break;

    case State::LookLeft:
      if (elapsed >= LOOK_LEFT_MS) {
        leftCm_ = sonar_.readCm();
        servo_.write(SERVO_RIGHT);
        go(State::LookRight);
      }
      break;

    case State::LookRight:
      if (elapsed >= LOOK_RIGHT_MS) {
        const long rightCm = sonar_.readCm();
        servo_.write(SERVO_CENTER);
        maneuver_ = planManeuver(leftCm_, rightCm, DEAD_END_DISTANCE_CM);
        chassis_.drive(maneuver_.first.move);
        go(State::FirstMove);
      }
      break;

    case State::FirstMove:
      if (elapsed >= maneuver_.first.durationMs) {
        chassis_.drive(maneuver_.second.move);
        go(State::SecondMove);
      }
      break;

    case State::SecondMove:
      if (elapsed >= maneuver_.second.durationMs) {
        chassis_.stop();
        go(State::Recenter);
      }
      break;

    case State::Recenter:
      if (elapsed >= RECENTER_MS) {
        go(State::Cruise);
      }
      break;
  }
}

void ObstacleAvoidMode::cruise(unsigned long now) {
  if (now - lastMeasureAt_ < MEASURE_INTERVAL_MS) {
    return;
  }
  lastMeasureAt_ = now;

  const long frontCm = sonar_.readCm();
  warningLed_.set(frontCm < LED_WARNING_DISTANCE_CM);

  if (frontCm < OBSTACLE_DISTANCE_CM) {
    chassis_.stop();
    servo_.write(SERVO_LEFT);
    go(State::LookLeft);
  } else {
    chassis_.drive(Drive::Forward);
  }
}
