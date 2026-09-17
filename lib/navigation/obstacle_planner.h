#pragma once

#include "drive.h"

struct Step {
  Drive move;
  uint16_t durationMs;
};

struct Maneuver {
  Step first;
  Step second;
};

// How to get around an obstacle given the free distance on each side: back up a little and
// turn to the side with more room. When both sides are closer than deadEndCm, back up further
// and turn around more.
Maneuver planManeuver(long leftCm, long rightCm, long deadEndCm);
