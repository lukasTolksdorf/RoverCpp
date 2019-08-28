#include "roverLib/Rover.hpp"

#include <iostream>

namespace RoverCpp {
namespace Rover {

Rover::Rover() noexcept : state_{0, 0, Orientation::NORTH}, wasCalibrated_(false), id_(generateNewId()) {
  // intentionally left empty
}

Rover::Rover(int x_, int y_, Orientation orientation_) noexcept
    : state_{x_, y_, orientation_}, wasCalibrated_(false), id_(generateNewId()) {
  // intentionally left empty
}

RoverStateType Rover::estimateState(CommandType command_) const {
  auto estimation = state_;

  auto turnRight = [&estimation, this](int rightTurns_) {
    const auto nElements = static_cast<int>(Orientation::N_ELEMENTS);

    // modulo with negativ numbers is well defined since C++11
    const auto offset = (rightTurns_ % nElements) + nElements;
    estimation.orientation = static_cast<Orientation>((static_cast<int>(state_.orientation) + offset) % nElements);
  };

  auto move = [&estimation, this]() {
    switch (state_.orientation) {
    case Orientation::EAST:
      ++(estimation.x);
      break;
    case Orientation::SOUTH:
      --(estimation.y);
      break;
    case Orientation::WEST:
      --(estimation.x);
      break;
    case Orientation::NORTH:
      ++(estimation.y);
      break;
    default:
      break;
    }
  };

  switch (command_) {
  case TURNRIGHT:
    turnRight(1);
    break;
  case TURNLEFT:
    turnRight(-1);
    break;
  case MOVE:
    move();
    break;
  default:
    // do nothing
    break;
  }

  return estimation;
}

const RoverStateType &Rover::executeCommand(CommandType command_) {
  if (!wasCalibrated_) {
    // log here
  }
  state_ = estimateState(command_);
  return state_;
}

const RoverStateType &Rover::calibrate(const StateType &newState_) {
  if (wasCalibrated_) {
    // log here
  }
  state_ = newState_;
  wasCalibrated_ = true;
  return state_;
}

int Rover::getStateX() const { return state_.x; }

int Rover::getStateY() const { return state_.y; }

Orientation Rover::getStateOrientation() const { return state_.orientation; }

const RoverStateType &Rover::getState() const { return state_; }

bool Rover::wasCalibrated() const { return wasCalibrated_; }
const std::string &Rover::getId() const { return id_; }

std::string Rover::generateNewId() {
  static int counter = 1;
  std::string id = "RVR_ID_" + std::to_string(counter);
  ++counter;
  return id;
}

bool operator==(const RoverStateType &lhs, const RoverStateType &rhs) {
  return ((lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.orientation == rhs.orientation));
}

bool operator!=(const RoverStateType &lhs, const RoverStateType &rhs) { return !(lhs == rhs); }

std::ostream &operator<<(std::ostream &os_, const RoverStateType &state_) {
  os_ << state_.x << ' ' << state_.y << ' ';
  switch (state_.orientation){
  case Orientation::NORTH:
    os_<<'N';
    break;
  case Orientation::EAST:
    os_<< 'E';
    break;
  case Orientation::SOUTH:
    os_<< 'S';
    break;
  case Orientation::WEST:
    os_<< 'W';
    break;
  default:
    os_ << "Unknown Orientation";
    break;
  }
  return os_;
}
} // namespace Rover
} // namespace RoverCpp
