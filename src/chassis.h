#pragma once

#include "drive.h"
#include "motors.h"

// Moves the tank in one of the fixed directions at the speeds from config.h.
class Chassis {
public:
  explicit Chassis(const Motors& motors) : motors_(motors) {}

  void drive(Drive direction) const;
  void stop() const;

private:
  const Motors& motors_;
};
