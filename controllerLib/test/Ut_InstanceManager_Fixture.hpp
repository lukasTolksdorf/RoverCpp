#ifndef ROVERCPP_CONTROLLERLIB_TEST_UT_INSTANCEMANAGER_FIXTURE_HPP_
#define ROVERCPP_CONTROLLERLIB_TEST_UT_INSTANCEMANAGER_FIXTURE_HPP_

#include "MockConstraintType.hpp"
#include "MockInstanceType.hpp"
#include "controllerLib/InstanceMananger.hpp"

#include "gtest/gtest.h"

namespace test {
namespace RoverCpp {
namespace Controller {

using InstanceManagerWithMocks = ::RoverCpp::Controller::InstanceManager<MockInstanceType, MockConstraintType>;

template <typename TestDataType> class Ut_InstanceManager_Fixture : public testing::TestWithParam<TestDataType> {
public:
  Ut_InstanceManager_Fixture()
      : testData(this->GetParam()), instance_manager(), mockedInstances(instance_manager.instances_),
        mockedConstraints(instance_manager.constraint_checker_) {
    // intentionally left empty
  }

  TestDataType testData;

  InstanceManagerWithMocks instance_manager;

  std::array<MockInstanceType, 4> &mockedInstances;
  MockConstraintType &mockedConstraints;

};

} // namespace Controller
} // namespace RoverCpp
} // namespace test

#endif // ROVERCPP_CONTROLLERLIB_TEST_UT_INSTANCEMANAGER_FIXTURE_HPP_
