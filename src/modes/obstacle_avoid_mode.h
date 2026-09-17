#pragma once

#include <Servo.h>

#include "chassis.h"
#include "led.h"
#include "mode.h"
#include "obstacle_planner.h"
#include "sonar.h"

// Drives forward on its own. When something is close it stops, looks left and right with the
// sonar on the servo, then backs up and turns to the freer side.
//
// Written as a state machine on millis() so the main loop keeps polling the remote.
class ObstacleAvoidMode final : public Mode {
public:
  ObstacleAvoidMode(const Chassis& chassis, const Sonar& sonar, Led& warningLed, uint8_t servoPin)
      : chassis_(chassis), sonar_(sonar), warningLed_(warningLed), servoPin_(servoPin) {}

  void begin();

  const __FlashStringHelper* name() const override;
  const uint8_t* icon() const override;
  void enter() override;
  void update() override;
  void exit() override;

private:
  enum class State : uint8_t {
    Cruise,
    LookLeft,
    LookRight,
    FirstMove,
    SecondMove,
    Recenter,
  };

  void go(State next);
  void cruise(unsigned long now);

  const Chassis& chassis_;
  const Sonar& sonar_;
  Led& warningLed_;
  uint8_t servoPin_;

  Servo servo_;
  State state_ = State::Recenter;
  unsigned long stateStartedAt_ = 0;
  unsigned long lastMeasureAt_ = 0;
  long leftCm_ = 0;
  Maneuver maneuver_ = {};
};
