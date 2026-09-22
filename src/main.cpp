#include <Arduino.h>

#include "board.h"
#include "chassis.h"
#include "config.h"
#include "ir_remote.h"
#include "led.h"
#include "led_matrix.h"
#include "modes/light_follow_mode.h"
#include "modes/manual_mode.h"
#include "modes/obstacle_avoid_mode.h"
#include "modes/serial_mode.h"
#include "motors.h"
#include "remote_keys.h"
#include "sonar.h"

namespace {

const Motors motors({PIN_MOTOR_LEFT_DIR, PIN_MOTOR_LEFT_PWM, PIN_MOTOR_RIGHT_DIR,
                     PIN_MOTOR_RIGHT_PWM});
const IrRemote remote;
const LedMatrix matrix({PIN_MATRIX_SCL, PIN_MATRIX_SDA});
const Sonar sonar({PIN_SONAR_TRIG, PIN_SONAR_ECHO});
Led frontLed(PIN_LED);
const Chassis chassis(motors);

ManualMode manualMode(chassis);
LightFollowMode lightFollowMode(chassis, {PIN_LIGHT_LEFT, PIN_LIGHT_RIGHT});
ObstacleAvoidMode obstacleAvoidMode(chassis, sonar, frontLed, PIN_SERVO);
SerialMode serialMode(chassis);

Mode* mode = &manualMode;

void switchTo(Mode& next) {
  mode->exit();
  chassis.stop();
  frontLed.set(false);

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
    case IR_KEY_3:
      switchTo(obstacleAvoidMode);
      break;
    case IR_KEY_4:
      switchTo(serialMode);
      break;
    case IR_KEY_STAR:
      frontLed.toggle();
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
  sonar.begin();
  frontLed.begin();
  obstacleAvoidMode.begin();

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
