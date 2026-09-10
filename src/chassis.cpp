#include "chassis.h"

#include "config.h"

namespace {

constexpr DriveSpeeds SPEEDS = {SPEED_FORWARD, SPEED_BACKWARD, SPEED_TURN};

}  // namespace

void Chassis::drive(Drive direction) const {
  const TrackSpeeds tracks = trackSpeeds(direction, SPEEDS);
  motors_.set(tracks.left, tracks.right);
}

void Chassis::stop() const {
  motors_.stop();
}
