#pragma once

#include "chassis.h"
#include "mode.h"

// Arrow keys drive the tank. It keeps moving until another key is pressed.
class ManualMode final : public Mode {
public:
  explicit ManualMode(const Chassis& chassis) : chassis_(chassis) {}

  const __FlashStringHelper* name() const override;
  const uint8_t* icon() const override;
  void onKey(uint8_t key) override;

private:
  const Chassis& chassis_;
};
