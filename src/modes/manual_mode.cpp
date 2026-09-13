#include "manual_mode.h"

#include "icons.h"
#include "remote_keys.h"

const __FlashStringHelper* ManualMode::name() const {
  return F("manual");
}

const uint8_t* ManualMode::icon() const {
  return icons::SMILE;
}

void ManualMode::onKey(uint8_t key) {
  switch (key) {
    case IR_KEY_UP:
      chassis_.drive(Drive::Forward);
      break;
    case IR_KEY_DOWN:
      chassis_.drive(Drive::Backward);
      break;
    case IR_KEY_LEFT:
      chassis_.drive(Drive::Left);
      break;
    case IR_KEY_RIGHT:
      chassis_.drive(Drive::Right);
      break;
    default:
      break;
  }
}
