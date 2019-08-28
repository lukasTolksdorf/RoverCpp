#ifndef ROVERCPP_CONTROLLERLIB_TEST_UT_CONTROLLERPOLICYCLASS_FIXTURE_HPP_
#define ROVERCPP_CONTROLLERLIB_TEST_UT_CONTROLLERPOLICYCLASS_FIXTURE_HPP_

#include "FakeCommandDecoder.hpp"
#include "MockInstanceManager.hpp"
#include "controllerLib/ControllerPolicyClass.hpp"

#include "gtest/gtest.h"

namespace test {
namespace RoverCpp {
namespace Controller {

MATCHER_P(SStreamMatchesString, cmp, "the streams content did not match the given string"){
  std::string string_arg = arg.str();
  return string_arg == cmp;
}

class Ut_ControllerPolicyClass_Fixture : public ::testing::Test {
public:
  Ut_ControllerPolicyClass_Fixture() {
    // intentionally left empty
  }

  ::RoverCpp::Controller::Controller_PolicyClass<FakeCommandDecoder, MockInstanceManager> controller;

};
} // namespace Controller
} // namespace RoverCpp
} // namespace test
#endif // ROVERCPP_CONTROLLERLIB_TEST_UT_CONTROLLERPOLICYCLASS_FIXTURE_HPP_
