#include "light_steering.h"

Drive steerToLight(int left, int right, int threshold) {
  const bool leftLit = left > threshold;
  const bool rightLit = right > threshold;

  if (leftLit && rightLit) {
    return Drive::Forward;
  }
  if (leftLit) {
    return Drive::Left;
  }
  if (rightLit) {
    return Drive::Right;
  }
  return Drive::Stop;
}
