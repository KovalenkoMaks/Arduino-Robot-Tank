#pragma once

#include "drive.h"

// Where to go given the two photoresistor readings. A side is lit when its reading is above
// the threshold: both lit means the light is ahead, none means there is nothing to follow.
Drive steerToLight(int left, int right, int threshold);
