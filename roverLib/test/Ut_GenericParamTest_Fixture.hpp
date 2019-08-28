#ifndef ROVERCPP_UT_GENERICHPARAMTEST_FIXTURE_HPP_
#define ROVERCPP_UT_GENERICHPARAMTEST_FIXTURE_HPP_

#include "gtest/gtest.h"

namespace test {
namespace RoverCpp {
namespace Rover {
template <class TestDataType, class TestInstanceType> class Ut_GenericParamTest_Fixture : public testing::TestWithParam<TestDataType> {
public:
  Ut_GenericParamTest_Fixture() : testData(this->GetParam()), testInstance() {
    // intentionally left empty
  };
  TestDataType testData;
  TestInstanceType testInstance;
};

} // namespace Rover
} // namespace RoverCpp
} // namespace test

#endif // ROVERCPP_UT_GENERICHPARAMTEST_FIXTURE_HPP_
