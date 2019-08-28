#ifndef ROVERCPP_CONTROLLERLIB_TEST_UT_ISTREAMROUTER_FIXTURE_HPP_
#define ROVERCPP_CONTROLLERLIB_TEST_UT_ISTREAMROUTER_FIXTURE_HPP_

#include "controllerLib/IStreamRouter.hpp"
#include "MockControllerType.hpp"

#include "gtest/gtest.h"

namespace test {
namespace RoverCpp {
namespace Controller {

MATCHER_P(SStreamMatchesString, cmp, "the streams content did not match the given string"){
  std::string string_arg = arg.str();
  return string_arg == cmp;
}

class Ut_IStreamRouter_Fixture : public testing::Test {
public:
  Ut_IStreamRouter_Fixture() : router_instance(), mocked_controller(router_instance.controller_instance_){
    // intentionally left empty
  }

  ::RoverCpp::Controller::IStreamRouter<MockControllerType> router_instance;
  MockControllerType& mocked_controller;
};

} // namespace Controller
} // namespace RoverCpp
} // namespace test

#endif // ROVERCPP_CONTROLLERLIB_TEST_UT_ISTREAMROUTER_FIXTURE_HPP_
