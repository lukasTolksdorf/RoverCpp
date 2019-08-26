#include "roverLib/Rover.hpp"

namespace RoverCpp {

Rover::Rover(int x_, int y_, Orientation orientation_) noexcept
    : state_{x_, y_, orientation_} {
  // intentionally left empty
}

Rover::StateType Rover::estimateState(Rover::CommandType command_) const {
  auto estimation = state_;

  auto turnRight = [&estimation, this](int rightTurns_) {
    const auto nElements = static_cast<int>(Orientation::N_ELEMENTS);

    // modulo with negativ numbers is well defined since C++11
    const auto offset = (rightTurns_ % nElements) + nElements;
    estimation.orientation = static_cast<Orientation>(
        (static_cast<int>(state_.orientation) + offset) % nElements);
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

const Rover::StateType &Rover::executeCommand(Rover::CommandType command_) {
  state_ = estimateState(command_);
  return state_;
}

int Rover::getStateX() const { return state_.x; }

int Rover::getStateY() const { return state_.y; }

Orientation Rover::getStateOrientation() const { return state_.orientation; }

const Rover::StateType &Rover::getState() const { return state_; }

bool operator==(const Rover::StateType &lhs, const Rover::StateType &rhs) {
  return ((lhs.x == rhs.x) && (lhs.y == rhs.y) &&
          (lhs.orientation == rhs.orientation));
}

bool operator!=(const Rover::StateType &lhs, const Rover::StateType &rhs) {
  return !(lhs == rhs);
}
}