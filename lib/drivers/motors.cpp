#include "motors.h"

namespace {

// The driver board moves a track forward when its direction pin is LOW.
void setTrack(uint8_t dirPin, uint8_t pwmPin, int16_t speed) {
  digitalWrite(dirPin, speed >= 0 ? LOW : HIGH);
  analogWrite(pwmPin, constrain(abs(speed), 0, 255));
}

}  // namespace

void Motors::begin() const {
  pinMode(pins_.leftDir, OUTPUT);
  pinMode(pins_.leftPwm, OUTPUT);
  pinMode(pins_.rightDir, OUTPUT);
  pinMode(pins_.rightPwm, OUTPUT);
  stop();
}

void Motors::set(int16_t left, int16_t right) const {
  setTrack(pins_.leftDir, pins_.leftPwm, left);
  setTrack(pins_.rightDir, pins_.rightPwm, right);
}

void Motors::stop() const {
  set(0, 0);
}
