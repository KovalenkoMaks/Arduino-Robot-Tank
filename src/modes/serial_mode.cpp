#include "serial_mode.h"

#include "icons.h"
#include "serial_command.h"

const __FlashStringHelper* SerialMode::name() const {
  return F("serial control");
}

const uint8_t* SerialMode::icon() const {
  return icons::TEXT_BT;
}

void SerialMode::update() {
  if (Serial.available() == 0) {
    return;
  }

  Drive direction;
  if (parseDriveCommand(static_cast<char>(Serial.read()), direction)) {
    chassis_.drive(direction);
  }
}
