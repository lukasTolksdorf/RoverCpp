#include "roverLib/RoverConstraints.hpp"

namespace RoverCpp {
namespace Rover {

RoverConstraints::RoverConstraints() : xLim(0), yLim(0) {
  // intentionally left empty
}
void RoverConstraints::setBoundaries(int x, int y) {
  xLim = x;
  yLim = y;
}
bool RoverConstraints::isInBound(const RoverStateType &state) const {
  return ((state.x <= xLim) && (state.x >= 0) && (state.y <= yLim) && (state.y >= 0));
}
bool RoverConstraints::isCollision(const RoverStateType &lhs, const RoverStateType &rhs) { return ((lhs.x == rhs.x) && (lhs.y == rhs.y)); }

} // namespace Rover
} // namespace RoverCpp
