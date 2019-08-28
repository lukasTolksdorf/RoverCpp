
#ifndef ROVERCPP_CONTROLLERLIB_STRINGSTREAMCOMMANDDECODER_HPP_
#define ROVERCPP_CONTROLLERLIB_STRINGSTREAMCOMMANDDECODER_HPP_

#include "roverLib/Rover.hpp"

#include <experimental/optional>
#include <sstream>

namespace RoverCpp {
namespace Rover {

class StringStreamRoverDecoder {
public:

  static std::experimental::optional<RoverCommandType> popTopCommand(std::stringstream &);

  static RoverStateType decodeCalibrationInput(std::stringstream &input);
};

} // namespace Rover
} // namespace RoverCpp

#endif // ROVERCPP_CONTROLLERLIB_STRINGSTREAMCOMMANDDECODER_HPP_
