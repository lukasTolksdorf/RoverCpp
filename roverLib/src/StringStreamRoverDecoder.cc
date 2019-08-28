#include "roverLib/StringStreamRoverDecoder.hpp"

namespace RoverCpp {
namespace Rover {

std::experimental::optional<RoverCommandType> StringStreamRoverDecoder::popTopCommand(std::stringstream &input) {
  if (input.eof()) {
    return {std::experimental::nullopt};
  }
  char cmd = 'X';
  input >> cmd;

  switch (cmd) {
  case 'L':
    return {TURNLEFT};
  case 'R':
    return {TURNRIGHT};
  case 'M':
    return {MOVE};
  default:
    return {std::experimental::nullopt};
  }
}

RoverStateType StringStreamRoverDecoder::decodeCalibrationInput(std::stringstream &input) {
  int x, y;
  char orientation;

  input >> x >> y >> orientation;
  switch (orientation) {
  case 'N':
    return {x, y, Orientation::NORTH};
  case 'E':
    return {x, y, Orientation::EAST};
  case 'S':
    return {x, y, Orientation::SOUTH};
  case 'W':
    return {x, y, Orientation::WEST};
  default:
    // log here
    return {x, y, Orientation::NORTH};
  }
}

} // namespace Controller
} // namespace RoverCpp