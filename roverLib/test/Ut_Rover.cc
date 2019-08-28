#include "Ut_Rover_Fixture.hpp"

namespace test {
namespace RoverCpp {
namespace Rover {

/*
 * \description   This Ut verifies that a rover is correctly instantiated
 *                and is in the correct state
 *
 * \init          none
 *
 * \testAction    instantiate a rover instance with a given state
 *
 * \testResult    the rover shall be in the state as given at construction
 *
 */
TEST(UtRover, CreateRoverAtPosition) {
  {
    auto rover = ::RoverCpp::Rover::Rover(1, 2, ::RoverCpp::Orientation::WEST);

    EXPECT_EQ(1, rover.getStateX());
    EXPECT_EQ(2, rover.getStateY());
    EXPECT_EQ(::RoverCpp::Orientation::WEST, rover.getStateOrientation());
  }
}

struct RoverTurnTestDataType {
  ::RoverCpp::Rover::RoverCommandType command;
  ::RoverCpp::Orientation expectedOrientation;
};

// clang-format off
const GeneralRoverTestVectorType<RoverTurnTestDataType> roverTurnTestData{
    {// TestCase 1
     // initial state
     {0, 0, ::RoverCpp::Orientation::NORTH},
     // procedural data
     {
         // command                       expected orientation
         {::RoverCpp::Rover::TURNLEFT, ::RoverCpp::Orientation::WEST },
         {::RoverCpp::Rover::TURNLEFT, ::RoverCpp::Orientation::SOUTH},
         {::RoverCpp::Rover::TURNLEFT, ::RoverCpp::Orientation::EAST },
         {::RoverCpp::Rover::TURNLEFT, ::RoverCpp::Orientation::NORTH},
         {::RoverCpp::Rover::TURNLEFT, ::RoverCpp::Orientation::WEST },
         {::RoverCpp::Rover::TURNLEFT, ::RoverCpp::Orientation::SOUTH},
         {::RoverCpp::Rover::TURNLEFT, ::RoverCpp::Orientation::EAST },
         {::RoverCpp::Rover::TURNLEFT, ::RoverCpp::Orientation::NORTH},
     }},
    {// TestCase 2
     // initial state
     {0, 0, ::RoverCpp::Orientation::SOUTH},
     // procedural data
     {
         // command                       expected orientation
         {::RoverCpp::Rover::TURNRIGHT, ::RoverCpp::Orientation::WEST },
         {::RoverCpp::Rover::TURNRIGHT, ::RoverCpp::Orientation::NORTH},
         {::RoverCpp::Rover::TURNRIGHT, ::RoverCpp::Orientation::EAST },
         {::RoverCpp::Rover::TURNRIGHT, ::RoverCpp::Orientation::SOUTH},
         {::RoverCpp::Rover::TURNRIGHT, ::RoverCpp::Orientation::WEST },
         {::RoverCpp::Rover::TURNRIGHT, ::RoverCpp::Orientation::NORTH},
         {::RoverCpp::Rover::TURNRIGHT, ::RoverCpp::Orientation::EAST },
         {::RoverCpp::Rover::TURNRIGHT, ::RoverCpp::Orientation::SOUTH},
     }

    },
    {// TestCase 3
     // initial state
     {0, 0, ::RoverCpp::Orientation::EAST},
     // procedural data
     {
         // command                       expected orientation
         {::RoverCpp::Rover::TURNRIGHT, ::RoverCpp::Orientation::SOUTH},
         {::RoverCpp::Rover::TURNLEFT,  ::RoverCpp::Orientation::EAST },
         {::RoverCpp::Rover::TURNRIGHT, ::RoverCpp::Orientation::SOUTH},
         {::RoverCpp::Rover::TURNLEFT,  ::RoverCpp::Orientation::EAST },
     }

    },
};
// clang-format on

using UtRoverTurnFixture_P = UtRoverFixture_P<RoverTurnTestDataType>;

INSTANTIATE_TEST_CASE_P(/* empty prefix*/, UtRoverTurnFixture_P, ::testing::ValuesIn(roverTurnTestData));

/*
 * \description   This Ut test the turning mechanics of the rover
 *
 * \init          instantiate a rover with the initial state from
 *                roverTurnTestData
 *
 * \testAction    Execute all commands with a prior prediction as described in
 *                the procedural data of roverTurnTestData
 *
 * \testResult    after every executed command, the rover's orientation shall
 *                match the expected orientation as described in
 *                roverTurnTestData. The x and y positions shall remain in their
 *                initial state.
 */
TEST_P(UtRoverTurnFixture_P, Turning) {
  EXPECT_EQ(rover.getState(), testData.initialState);

  for (auto &step : testData.proceduralData) {
    // testAction
    const auto predictedState = rover.estimateState(step.command);
    EXPECT_NE(rover.getState(), predictedState);

    rover.executeCommand(step.command);

    // testResult
    EXPECT_EQ(rover.getStateOrientation(), step.expectedOrientation);
    EXPECT_EQ(rover.getStateX(), testData.initialState.x);
    EXPECT_EQ(rover.getStateY(), testData.initialState.y);
    EXPECT_EQ(rover.getState(), predictedState);
  }
}

struct RoverMoveTestDataType {
  ::RoverCpp::Rover::RoverCommandType command;
  decltype(::RoverCpp::Rover::RoverStateType::x) expected_x;
  decltype(::RoverCpp::Rover::RoverStateType::y) expected_y;
};

// clang-format off
const GeneralRoverTestVectorType<RoverMoveTestDataType> roverMoveTestData = {
    {// TestCase 1
     // initial state
     {0, -3, ::RoverCpp::Orientation::NORTH},
     // procedural data
     {//  command                 expected_x    expected_y
         {::RoverCpp::Rover::MOVE,    0,           -2},
         {::RoverCpp::Rover::MOVE,    0,           -1},
         {::RoverCpp::Rover::MOVE,    0,           -0},
         {::RoverCpp::Rover::MOVE,    0,            1},
         {::RoverCpp::Rover::MOVE,    0,            2},
         {::RoverCpp::Rover::MOVE,    0,            3},
     }},
    {// TestCase 2
     // initial state
     {0, 3, ::RoverCpp::Orientation::SOUTH},
     // procedural data
     {//  command                 expected_x    expected_y
         {::RoverCpp::Rover::MOVE,    0,            2},
         {::RoverCpp::Rover::MOVE,    0,            1},
         {::RoverCpp::Rover::MOVE,    0,            0},
         {::RoverCpp::Rover::MOVE,    0,           -1},
         {::RoverCpp::Rover::MOVE,    0,           -2},
         {::RoverCpp::Rover::MOVE,    0,           -3},
     }},
    {// TestCase 3
     // initial state
     {-3, 0, ::RoverCpp::Orientation::EAST},
     // procedural data
     {//  command                 expected_x    expected_y
         {::RoverCpp::Rover::MOVE,   -2,            0},
         {::RoverCpp::Rover::MOVE,   -1,            0},
         {::RoverCpp::Rover::MOVE,    0,            0},
         {::RoverCpp::Rover::MOVE,    1,            0},
         {::RoverCpp::Rover::MOVE,    2,            0},
         {::RoverCpp::Rover::MOVE,    3,            0},
     }},
    {// TestCase 4
     // initial state
     {3, 0, ::RoverCpp::Orientation::WEST},
     // procedural data
     {//  command                 expected_x    expected_y
         {::RoverCpp::Rover::MOVE,    2,            0},
         {::RoverCpp::Rover::MOVE,    1,            0},
         {::RoverCpp::Rover::MOVE,    0,            0},
         {::RoverCpp::Rover::MOVE,   -1,            0},
         {::RoverCpp::Rover::MOVE,   -2,            0},
         {::RoverCpp::Rover::MOVE,   -3,            0},
     }},
};
// clang-format on

using UtRoverMoveFixture_P = UtRoverFixture_P<RoverMoveTestDataType>;

INSTANTIATE_TEST_CASE_P(/* empty prefix*/, UtRoverMoveFixture_P, ::testing::ValuesIn(roverMoveTestData));

/*
 * \description   This Ut test the move mechanics of the rover
 *
 * \init          instantiate a rover with the initial state from
 *                roverMoveTestData
 *
 * \testAction    Execute all commands with a prior state prediction as
 *                described in the procedural data of roverMoveTestData.
 *
 * \testResult    after every executed command, the rover's state shall match
 *                the prediction and its x and y position shall match the
 *                expected position as described in the procedural data from
 *                roverMoveTestData. The rover's orientation shall remain in its
 *                initial state.
 */
TEST_P(UtRoverMoveFixture_P, Move) {

  EXPECT_EQ(rover.getState(), testData.initialState);

  for (auto &step : testData.proceduralData) {

    // testAction
    const auto predictedState = rover.estimateState(step.command);
    EXPECT_NE(rover.getState(), predictedState);

    rover.executeCommand(step.command);

    // testResult
    EXPECT_EQ(rover.getState(), (::RoverCpp::Rover::RoverStateType{step.expected_x, step.expected_y, testData.initialState.orientation}));
    EXPECT_EQ(rover.getState(), predictedState);
  }
}

struct RoverCommandInteractionTestDataType {
  ::RoverCpp::Rover::RoverCommandType command;
  ::RoverCpp::Rover::RoverStateType expectedState;
};

const GeneralRoverTestVectorType<RoverCommandInteractionTestDataType> commandInteractionTestData = {
    {// TestCase 1
     // initial state
     {0, 0, ::RoverCpp::Orientation::NORTH},
     // procedural data
     {
         // clang-format off
             {::RoverCpp::Rover::MOVE,      {  0,  1, ::RoverCpp::Orientation::NORTH}},
             {::RoverCpp::Rover::TURNLEFT,  {  0,  1, ::RoverCpp::Orientation::WEST}},
             {::RoverCpp::Rover::MOVE,      { -1,  1, ::RoverCpp::Orientation::WEST}},
             {::RoverCpp::Rover::MOVE,      { -2,  1, ::RoverCpp::Orientation::WEST}},
             {::RoverCpp::Rover::TURNLEFT,  { -2,  1, ::RoverCpp::Orientation::SOUTH}},
             {::RoverCpp::Rover::MOVE,      { -2,  0, ::RoverCpp::Orientation::SOUTH}},
             {::RoverCpp::Rover::TURNLEFT,  { -2,  0, ::RoverCpp::Orientation::EAST}},
             {::RoverCpp::Rover::MOVE,      { -1,  0, ::RoverCpp::Orientation::EAST}},
             {::RoverCpp::Rover::MOVE,      {  0,  0, ::RoverCpp::Orientation::EAST}},
         // clang-format on
     }},
};

using UtRoverCommandInteractionFixture_P = UtRoverFixture_P<RoverCommandInteractionTestDataType>;

INSTANTIATE_TEST_CASE_P(/* empty prefix*/, UtRoverCommandInteractionFixture_P, ::testing::ValuesIn(commandInteractionTestData));

/*
 * \description   This Ut tests the interaction between the move and turn
 *                commands
 *
 * \init          instantiates a rover with the initial state from
 *                RoverCommandInteractionTestData
 *
 * \testAction    Execute all commands with a prior state prediction as
 *                described in the procedural data of
 *                RoverCommandInteractionTestData.
 *
 * \testResult    after every command execution, the rover's state shall match
 *                the prior prediction and the expected state given in the
 *                procedural data in RoverCommandInteractionTestData
 */
TEST_P(UtRoverCommandInteractionFixture_P, CommandInteraction) {

  EXPECT_EQ(rover.getState(), testData.initialState);

  for (auto &step : testData.proceduralData) {
    // testAction
    const auto predictedState = rover.estimateState(step.command);
    EXPECT_NE(rover.getState(), predictedState);

    rover.executeCommand(step.command);

    // testResult
    EXPECT_EQ(rover.getState(), predictedState);
    EXPECT_EQ(rover.getState(), step.expectedState);
  }
}

} // namespace Rover
} // namespace RoverCpp
} // namespace test
