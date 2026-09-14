#include <Arduino.h>

#include "board.h"
#include "chassis.h"
#include "config.h"
#include "ir_remote.h"
#include "led_matrix.h"
#include "modes/light_follow_mode.h"
#include "modes/manual_mode.h"
#include "motors.h"
#include "remote_keys.h"

namespace {

const Motors motors({PIN_MOTOR_LEFT_DIR, PIN_MOTOR_LEFT_PWM, PIN_MOTOR_RIGHT_DIR,
                     PIN_MOTOR_RIGHT_PWM});
const IrRemote remote;
const LedMatrix matrix({PIN_MATRIX_SCL, PIN_MATRIX_SDA});
const Chassis chassis(motors);

ManualMode manualMode(chassis);
LightFollowMode lightFollowMode(chassis, {PIN_LIGHT_LEFT, PIN_LIGHT_RIGHT});

Mode* mode = &manualMode;

void switchTo(Mode& next) {
  mode->exit();
  chassis.stop();

  mode = &next;
  mode->enter();
  matrix.show(mode->icon());
  Serial.print(F("Mode: "));
  Serial.println(mode->name());
}

void handleKey(uint8_t key) {
  switch (key) {
    case IR_KEY_OK:
    case IR_KEY_1:
      switchTo(manualMode);
      break;
    case IR_KEY_2:
      switchTo(lightFollowMode);
      break;
    default:
      mode->onKey(key);
      break;
  }
}

}  // namespace

void setup() {
  Serial.begin(SERIAL_BAUD);
  motors.begin();
  remote.begin();
  matrix.begin();

  switchTo(manualMode);
}

void loop() {
  uint8_t key;
  if (remote.poll(key)) {
    Serial.print(F("IR key: 0x"));
    Serial.println(key, HEX);
    handleKey(key);
  }

  mode->update();
}
