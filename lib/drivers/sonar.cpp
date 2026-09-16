#include "sonar.h"

namespace {

// About 4 m there and back. The default pulseIn() timeout is a full second.
constexpr unsigned long ECHO_TIMEOUT_US = 25000;
// Sound needs about 58 us to travel 1 cm and return.
constexpr unsigned long US_PER_CM = 58;

}  // namespace

void Sonar::begin() const {
  pinMode(pins_.trig, OUTPUT);
  pinMode(pins_.echo, INPUT);
}

long Sonar::readCm() const {
  digitalWrite(pins_.trig, LOW);
  delayMicroseconds(2);
  digitalWrite(pins_.trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pins_.trig, LOW);

  const unsigned long echoUs = pulseIn(pins_.echo, HIGH, ECHO_TIMEOUT_US);
  if (echoUs == 0) {
    return NO_ECHO_CM;
  }
  return echoUs / US_PER_CM;
}
