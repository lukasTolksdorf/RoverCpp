#ifndef ROVERCPP_ROVER_H
#define ROVERCPP_ROVER_H

#include "roverLib/Utility.hpp"
#include <iosfwd>
#include <string>
#include <utility>

namespace RoverCpp {
namespace Rover {

enum RoverCommandType {
  TURNLEFT,
  TURNRIGHT,
  MOVE,
};

struct RoverStateType {
  int x;
  int y;
  Orientation orientation;
};

class Rover {
public:
  Rover() noexcept;
  Rover(int x_, int y_, Orientation orientation_) noexcept;

  using StateType = RoverStateType;
  using CommandType = RoverCommandType;

  StateType estimateState(CommandType command_) const;
  const StateType &executeCommand(CommandType command_);
  const StateType &calibrate(const StateType &newState_);

  const StateType &getState() const;
  int getStateX() const;
  int getStateY() const;
  Orientation getStateOrientation() const;
  const std::string &getId() const;
  bool wasCalibrated() const;

private:
  StateType state_;
  bool wasCalibrated_;
  std::string id_;

  static std::string generateNewId();
};

bool operator==(const RoverStateType &lhs, const RoverStateType &rhs);
bool operator!=(const RoverStateType &lhs, const RoverStateType &rhs);
std::ostream &operator<<(std::ostream &os_, const RoverStateType &state_);

} // namespace Rover
} // namespace RoverCpp
#endif // ROVERCPP_ROVER_H
