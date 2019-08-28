#ifndef ROVERCPP_CONTROLLERLIB_TEST_MOCKCOMMANDDECODER_HPP_
#define ROVERCPP_CONTROLLERLIB_TEST_MOCKCOMMANDDECODER_HPP_

#include "MockInstanceType.hpp"
#include "gmock/gmock.h"

#include <experimental/optional>
#include <sstream>

namespace test {
namespace RoverCpp {
namespace Controller {


class FakeCommandDecoder {
public:
  FakeCommandDecoder();

  static MockInstanceType::StateType decodeCalibrationInput(std::stringstream &input);

  static std::experimental::optional<typename MockInstanceType::CommandType> popTopCommand(std::stringstream &input);

private:

  static int numCall;

};

} // namespace Controller
} // namespace RoverCpp
} // namespace test

#endif // ROVERCPP_CONTROLLERLIB_TEST_MOCKCOMMANDDECODER_HPP_
