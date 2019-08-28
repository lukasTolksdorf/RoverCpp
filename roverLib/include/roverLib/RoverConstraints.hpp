#ifndef ROVERCPP_ROVERLIB_ROVERCONSTRAINTS_HPP_
#define ROVERCPP_ROVERLIB_ROVERCONSTRAINTS_HPP_

#include "roverLib/Rover.hpp"

namespace RoverCpp {
namespace Rover {

class RoverConstraints {
public:
  RoverConstraints();

  void setBoundaries(int x, int y);

  bool isInBound(const RoverStateType &state) const;

  static bool isCollision(const RoverStateType &lhs, const RoverStateType &rhs);

private:
  int xLim;
  int yLim;
};
} // namespace Rover
} // namespace RoverCpp

#endif // ROVERCPP_ROVERLIB_ROVERCONSTRAINTS_HPP_
