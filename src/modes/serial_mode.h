#pragma once

#include "chassis.h"
#include "mode.h"

// Drives on commands from the serial port: a Bluetooth module on D0/D1 or the USB cable.
class SerialMode final : public Mode {
public:
  explicit SerialMode(const Chassis& chassis) : chassis_(chassis) {}

  const __FlashStringHelper* name() const override;
  const uint8_t* icon() const override;
  void update() override;

private:
  const Chassis& chassis_;
};
