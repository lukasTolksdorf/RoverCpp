#ifndef ROVERCPP_CONTROLLERLIB_TEST_MOCKINSTANCEMANAGER_HPP_
#define ROVERCPP_CONTROLLERLIB_TEST_MOCKINSTANCEMANAGER_HPP_

#include "MockInstanceType.hpp"
#include "gmock/gmock.h"

namespace test {
namespace RoverCpp {
namespace Controller {

class MockInstanceManager {
public:
  MockInstanceManager();

  MOCK_METHOD0(next, void(void));
  MOCK_METHOD1(calibrateCurrentInstance, void(const MockInstanceType::StateType &));
  MOCK_METHOD1(forwardCommandToCurrentInstance, void(MockInstanceType::CommandType));
  MOCK_METHOD2(setBoundaries, void(const int &, const int &));
};

} // namespace Controller
} // namespace RoverCpp
} // namespace test

#endif // ROVERCPP_CONTROLLERLIB_TEST_MOCKINSTANCEMANAGER_HPP_
