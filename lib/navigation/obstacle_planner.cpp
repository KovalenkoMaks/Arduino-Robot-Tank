#include "obstacle_planner.h"

Maneuver planManeuver(long leftCm, long rightCm, long deadEndCm) {
  if (leftCm < deadEndCm && rightCm < deadEndCm) {
    return {{Drive::Backward, 800}, {Drive::Left, 600}};
  }
  if (leftCm > rightCm) {
    return {{Drive::Backward, 300}, {Drive::Left, 500}};
  }
  return {{Drive::Backward, 300}, {Drive::Right, 500}};
}
