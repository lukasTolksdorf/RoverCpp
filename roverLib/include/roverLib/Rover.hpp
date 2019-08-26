#ifndef ROVERCPP_ROVER_H
#define ROVERCPP_ROVER_H

#include "roverLib/Utility.hpp"
#include <utility>

namespace RoverCpp {

class Rover {
public:
  enum CommandType {
    TURNLEFT,
    TURNRIGHT,
    MOVE,
  };

  struct StateType {
    int x;
    int y;
    Orientation orientation;
  };

  Rover(int x_, int y_, Orientation orientation_) noexcept;

  StateType estimateState(CommandType command_) const;
  const StateType &executeCommand(CommandType command_);

  const StateType &getState() const;
  int getStateX() const;
  int getStateY() const;
  Orientation getStateOrientation() const;

private:
  StateType state_;
};

bool operator==(const Rover::StateType &lhs, const Rover::StateType &rhs);
bool operator!=(const Rover::StateType &lhs, const Rover::StateType &rhs);

} // namespace RoverCpp
#endif // ROVERCPP_ROVER_H
