#include "light_follow_mode.h"

#include "config.h"
#include "icons.h"
#include "light_steering.h"

const __FlashStringHelper* LightFollowMode::name() const {
  return F("light follow");
}

const uint8_t* LightFollowMode::icon() const {
  return icons::LIGHT;
}

void LightFollowMode::update() {
  const int left = analogRead(pins_.left);
  const int right = analogRead(pins_.right);
  chassis_.drive(steerToLight(left, right, LIGHT_THRESHOLD));
}
