#ifndef ROVERCPP_CONTROLLERLIB_TEST_MOCKCONSTRAINTTYPE_HPP_
#define ROVERCPP_CONTROLLERLIB_TEST_MOCKCONSTRAINTTYPE_HPP_

#include "MockInstanceType.hpp"

#include "gmock/gmock.h"

namespace test {
namespace RoverCpp {
namespace Controller {

class MockConstraintType {
public:
  MockConstraintType();

  MOCK_METHOD2(setBoundaries, void(int, int));
  MOCK_CONST_METHOD1(isInBound, bool(const MockInstanceType::StateType &));
  MOCK_CONST_METHOD2(isCollision, bool(const MockInstanceType::StateType &, const MockInstanceType::StateType &));
};

} // namespace Controller
} // namespace RoverCpp
} // namespace test
#endif // ROVERCPP_CONTROLLERLIB_TEST_MOCKCONSTRAINTTYPE_HPP_
