#include "Ut_GenericParamTest_Fixture.hpp"
#include "roverLib/RoverConstraints.hpp"

#include "gtest/gtest.h"

namespace test {
namespace RoverCpp {
namespace Rover {

using ::RoverCpp::Orientation;

struct CollisionTestDataType {
  ::RoverCpp::Rover::RoverStateType state1;
  ::RoverCpp::Rover::RoverStateType state2;
  bool isCollision;
};
using Ut_RoverConstraint_Fixture_P = Ut_GenericParamTest_Fixture<CollisionTestDataType, ::RoverCpp::Rover::RoverConstraints>;

// clang-format off
const std::vector<CollisionTestDataType> CollisionTestData = {
    {{ 0, 0, Orientation::NORTH}, { 0, 0, Orientation::NORTH}, true },
    {{ 0, 0, Orientation::SOUTH}, { 0, 0, Orientation::NORTH}, true },
    {{ 0, 0, Orientation::EAST }, { 0, 0, Orientation::NORTH}, true },
    {{ 0, 0, Orientation::WEST }, { 0, 0, Orientation::NORTH}, true },
    {{ 1,-1, Orientation::EAST }, { 1,-1, Orientation::NORTH}, true },
    {{-1, 1, Orientation::WEST }, {-1, 1, Orientation::NORTH}, true },
    {{ 1, 0, Orientation::NORTH}, { 0, 0, Orientation::NORTH}, false},
    {{-1, 0, Orientation::NORTH}, { 0, 0, Orientation::NORTH}, false},
    {{ 0, 1, Orientation::NORTH}, { 0, 0, Orientation::NORTH}, false},
    {{ 0,-1, Orientation::NORTH}, { 0, 0, Orientation::NORTH}, false},
    {{ 1,-1, Orientation::NORTH}, { 0, 0, Orientation::NORTH}, false},
    {{-1,-1, Orientation::NORTH}, { 0, 0, Orientation::NORTH}, false},
    {{ 1, 1, Orientation::NORTH}, { 0, 0, Orientation::NORTH}, false},
    {{-1, 1, Orientation::NORTH}, { 0, 0, Orientation::NORTH}, false},
};
// clang-format on
INSTANTIATE_TEST_CASE_P(/*empty prefix*/, Ut_RoverConstraint_Fixture_P, ::testing::ValuesIn(CollisionTestData));

/*
 * \description   This Ut tests the collision detection
 *
 * \init          instantiates a RoverConstraint instance
 *
 * \testAction    call isCollision with the states defined in CollisionTestData
 *
 * \testResult    the return of isCollision shall match the expectation defined
 *                in CollisionTestData
 *
 */
TEST_P(Ut_RoverConstraint_Fixture_P, IsCollision) {

  const bool Result = testInstance.isCollision(testData.state1, testData.state2);
  EXPECT_EQ(Result, testData.isCollision);
}

struct IsInBoundTestDataType {
  int xLim;
  int yLim;
  ::RoverCpp::Rover::RoverStateType state;

  bool expectation;
};

using Ut_RoverConstraintBounds_Fixture_P = Ut_GenericParamTest_Fixture<IsInBoundTestDataType, ::RoverCpp::Rover::RoverConstraints>;

// clang-format off
const std::vector<IsInBoundTestDataType> IsInBoundTestData = {
    {3,5, { 0,  0, Orientation::NORTH}, true},
    {3,5, { 0,  0, Orientation::EAST }, true},
    {3,5, { 0,  0, Orientation::SOUTH}, true},
    {3,5, { 0,  0, Orientation::WEST }, true},
    {3,5, { 0,  1, Orientation::NORTH}, true},
    {3,5, { 0,  2, Orientation::NORTH}, true},
    {3,5, { 0,  3, Orientation::NORTH}, true},
    {3,5, { 0,  4, Orientation::NORTH}, true},
    {3,5, { 0,  5, Orientation::NORTH}, true},
    {3,5, { 0,  6, Orientation::NORTH}, false},
    {3,5, { 1,  0, Orientation::NORTH}, true},
    {3,5, { 2,  1, Orientation::NORTH}, true},
    {3,5, { 3,  0, Orientation::NORTH}, true},
    {3,5, { 4,  1, Orientation::NORTH}, false},
    {3,5, { 5,  6, Orientation::NORTH}, false},
    {3,5, {-1,  1, Orientation::NORTH}, false},
    {3,5, { 1, -1, Orientation::NORTH}, false},
    {3,5, {-1, -1, Orientation::NORTH}, false},
};

INSTANTIATE_TEST_CASE_P(/* empty prefix */, Ut_RoverConstraintBounds_Fixture_P, testing::ValuesIn(IsInBoundTestData));

/*
 * \description   This Ut test the correct behaviour of the boundary check
 *
 * \init          instantiate a RoverConstraints instance and set its bounds
 *                according to IsInBoundTestData
 *
 * \testAction    call IsInBound with given state from IsInBoundTestData
 *
 * \testResult    the return value is expected to match the expectation from
 *                IsInBoundTetData
 */
TEST_P(Ut_RoverConstraintBounds_Fixture_P, IsInBound){

  testInstance.setBoundaries(testData.xLim, testData.yLim);
  const bool Result = testInstance.isInBound(testData.state);
  EXPECT_EQ(Result, testData.expectation);
}

// clang-format on

} // namespace Rover
} // namespace RoverCpp
} // namespace test
