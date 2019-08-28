#ifndef ROVERCPP_CONTROLLERLIB_TEST_MOCKINSTANCETYPE_HPP_
#define ROVERCPP_CONTROLLERLIB_TEST_MOCKINSTANCETYPE_HPP_

#include "gmock/gmock.h"

namespace test {
namespace RoverCpp {
namespace Controller {

class MockInstanceType {
public:
  enum StateType {
    STATE1,
    STATE2,
    STATE3,
    STATE4,
  };

  enum CommandType {
    CMD1,
    CMD2,
    CMD3,
  };

  MockInstanceType();

  MOCK_CONST_METHOD1(estimateState, const StateType &(CommandType));
  MOCK_METHOD1(executeCommand, const StateType &(CommandType));
  MOCK_METHOD1(calibrate, const StateType &(const StateType &));
  MOCK_CONST_METHOD0(getState, const StateType &(void));
  MOCK_CONST_METHOD0(getId, const std::string &());
};

} // namespace Controller
} // namespace RoverCpp
} // namespace test

#endif // ROVERCPP_CONTROLLERLIB_TEST_MOCKINSTANCETYPE_HPP_
