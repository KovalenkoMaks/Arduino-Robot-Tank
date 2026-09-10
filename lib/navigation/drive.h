#pragma once

#include <stdint.h>

enum class Drive : uint8_t {
  Stop,
  Forward,
  Backward,
  Left,
  Right,
};

struct DriveSpeeds {
  uint8_t forward;
  uint8_t backward;
  uint8_t turn;
};

// Signed speed per track, negative is backward.
struct TrackSpeeds {
  int16_t left;
  int16_t right;
};

// Turns are done on the spot: the tracks run in opposite directions.
TrackSpeeds trackSpeeds(Drive direction, const DriveSpeeds& speeds);
