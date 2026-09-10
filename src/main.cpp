#include <Arduino.h>

#include "board.h"
#include "chassis.h"
#include "config.h"
#include "ir_remote.h"
#include "motors.h"
#include "remote_keys.h"

namespace {

const Motors motors({PIN_MOTOR_LEFT_DIR, PIN_MOTOR_LEFT_PWM, PIN_MOTOR_RIGHT_DIR,
                     PIN_MOTOR_RIGHT_PWM});
const IrRemote remote;
const Chassis chassis(motors);

void handleKey(uint8_t key) {
  switch (key) {
    case IR_KEY_UP:
      chassis.drive(Drive::Forward);
      break;
    case IR_KEY_DOWN:
      chassis.drive(Drive::Backward);
      break;
    case IR_KEY_LEFT:
      chassis.drive(Drive::Left);
      break;
    case IR_KEY_RIGHT:
      chassis.drive(Drive::Right);
      break;
    case IR_KEY_OK:
      chassis.stop();
      break;
    default:
      break;
  }
}

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
    handleKey(key);
  }
}
