#pragma once

#include "chassis.h"
#include "mode.h"

// Drives toward a flashlight using the two photoresistors on the front.
class LightFollowMode final : public Mode {
public:
  struct Pins {
    uint8_t left;
    uint8_t right;
  };

  LightFollowMode(const Chassis& chassis, const Pins& pins) : chassis_(chassis), pins_(pins) {}

  const __FlashStringHelper* name() const override;
  const uint8_t* icon() const override;
  void update() override;

private:
  const Chassis& chassis_;
  Pins pins_;
};
