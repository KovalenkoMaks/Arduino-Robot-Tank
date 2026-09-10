#include "drive.h"

TrackSpeeds trackSpeeds(Drive direction, const DriveSpeeds& speeds) {
  switch (direction) {
    case Drive::Forward:
      return {speeds.forward, speeds.forward};
    case Drive::Backward:
      return {static_cast<int16_t>(-speeds.backward), static_cast<int16_t>(-speeds.backward)};
    case Drive::Left:
      return {static_cast<int16_t>(-speeds.turn), speeds.turn};
    case Drive::Right:
      return {speeds.turn, static_cast<int16_t>(-speeds.turn)};
    case Drive::Stop:
    default:
      return {0, 0};
  }
}
