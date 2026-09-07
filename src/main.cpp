#include <Arduino.h>

#include "board.h"
#include "config.h"
#include "motors.h"

namespace {

const Motors motors({PIN_MOTOR_LEFT_DIR, PIN_MOTOR_LEFT_PWM, PIN_MOTOR_RIGHT_DIR,
                     PIN_MOTOR_RIGHT_PWM});

}  // namespace

void setup() {
  Serial.begin(SERIAL_BAUD);
  motors.begin();
}

void loop() {}
