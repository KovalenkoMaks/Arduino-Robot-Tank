#pragma once

#include "drive.h"

// One-letter drive commands: U, D, L, R and S (stop), in either case.
// Returns false for anything else and leaves the output untouched.
bool parseDriveCommand(char command, Drive& direction);
