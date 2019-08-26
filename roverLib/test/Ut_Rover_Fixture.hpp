#ifndef ROVERCPP_UT_ROVER_FIXTURE_HPP_
#define ROVERCPP_UT_ROVER_FIXTURE_HPP_

#include "roverLib/Rover.hpp"
#include "gtest/gtest.h"

#include <vector>

namespace test {
namespace RoverCpp {

template <typename SpecificTestDataType> struct RoverTestDataType {
  ::RoverCpp::Rover::StateType initialState;
  std::vector<SpecificTestDataType> proceduralData;
};

template <typename ProceduralTestDataType>
using GeneralRoverTestVectorType = std::vector<RoverTestDataType<ProceduralTestDataType>>;

template <class TestDataType>
class UtRoverFixture_P : public testing::TestWithParam<RoverTestDataType<TestDataType>> {
public:
  UtRoverFixture_P() : testData(this->GetParam()), rover(testData.initialState.x, testData.initialState.y, testData.initialState.orientation){};

  RoverTestDataType<TestDataType> testData;
  ::RoverCpp::Rover rover;
};


} // namespace RoverCpp
} // namespace test
#endif // ROVERCPP_UT_ROVER_FIXTURE_HPP_
