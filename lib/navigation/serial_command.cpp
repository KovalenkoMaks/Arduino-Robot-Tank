#include "serial_command.h"

bool parseDriveCommand(char command, Drive& direction) {
  switch (command) {
    case 'U':
    case 'u':
      direction = Drive::Forward;
      return true;
    case 'D':
    case 'd':
      direction = Drive::Backward;
      return true;
    case 'L':
    case 'l':
      direction = Drive::Left;
      return true;
    case 'R':
    case 'r':
      direction = Drive::Right;
      return true;
    case 'S':
    case 's':
      direction = Drive::Stop;
      return true;
    default:
      return false;
  }
}
