#include <Arduino.h>

#include "board.h"
#include "config.h"
#include "ir_remote.h"
#include "motors.h"

namespace {

const Motors motors({PIN_MOTOR_LEFT_DIR, PIN_MOTOR_LEFT_PWM, PIN_MOTOR_RIGHT_DIR,
                     PIN_MOTOR_RIGHT_PWM});
const IrRemote remote;

}  // namespace

void setup() {
  Serial.begin(SERIAL_BAUD);
  motors.begin();
  remote.begin();
}

void loop() {
  uint8_t key;
  if (remote.poll(key)) {
    Serial.print(F("IR key: 0x"));
    Serial.println(key, HEX);
  }
}
