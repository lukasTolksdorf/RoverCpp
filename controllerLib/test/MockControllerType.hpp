#ifndef ROVERCPP_CONTROLLERLIB_TEST_MOCKCONTROLLERTYPE_HPP_
#define ROVERCPP_CONTROLLERLIB_TEST_MOCKCONTROLLERTYPE_HPP_

#include "gmock/gmock.h"

#include <sstream>

namespace test {
namespace RoverCpp {
namespace Controller {

class MockControllerType {
public:
  MockControllerType();

  MOCK_METHOD0(nextInstance, void(void));
  MOCK_METHOD1(processCalibrationInput, void(std::stringstream &));
  MOCK_METHOD1(processCommands, void(std::stringstream &));
  MOCK_METHOD2(setBoundaries, void(int, int));
};
} // namespace Controller
} // namespace RoverCpp
} // namespace test

#endif // ROVERCPP_CONTROLLERLIB_TEST_MOCKCONTROLLERTYPE_HPP_
