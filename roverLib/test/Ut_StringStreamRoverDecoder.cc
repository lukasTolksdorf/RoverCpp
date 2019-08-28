#include "Ut_GenericParamTest_Fixture.hpp"
#include "roverLib/StringStreamRoverDecoder.hpp"

#include "gtest/gtest.h"

#include <sstream>
#include <string>

namespace test {
namespace RoverCpp {
namespace Rover {

using ::RoverCpp::Rover::RoverCommandType;

struct PopTopCommandTestType {
  std::string input;
  std::vector<RoverCommandType> commands;
};

using Ut_StringStreamRoverDecoderPopTopCommand_Fixture_P = Ut_GenericParamTest_Fixture<PopTopCommandTestType, void *>;

// clang-format off
const std::vector<PopTopCommandTestType> PopTopCommandTestData = {
    {std::string("MLRMM"),
     {
      RoverCommandType::MOVE,
      RoverCommandType::TURNLEFT,
      RoverCommandType::TURNRIGHT,
      RoverCommandType::MOVE,
      RoverCommandType::MOVE,
     }},
    {std::string("LLL"),
     {
      RoverCommandType::TURNLEFT,
      RoverCommandType::TURNLEFT,
      RoverCommandType::TURNLEFT,
     }},
    {std::string("LRLRLRLR"),
     {
         RoverCommandType::TURNLEFT,
         RoverCommandType::TURNRIGHT,
         RoverCommandType::TURNLEFT,
         RoverCommandType::TURNRIGHT,
         RoverCommandType::TURNLEFT,
         RoverCommandType::TURNRIGHT,
         RoverCommandType::TURNLEFT,
         RoverCommandType::TURNRIGHT,
     }},
};
// clang-format on

INSTANTIATE_TEST_CASE_P(/* empty prefix */, Ut_StringStreamRoverDecoderPopTopCommand_Fixture_P, ::testing::ValuesIn(PopTopCommandTestData));

/*
 * \description   This ut tests the popTopCommand functionality
 *
 * \init          instantiate a stringstream with the data from
 *                PopTopCommandTestData
 *
 * \testAction    call popTopCommand with stringstream as long
 *                as no null_opt as returned
 *
 * \testResult    the returned commands must match the expected
 *                commands from PopTopCommandTestData
 */
TEST_P(Ut_StringStreamRoverDecoderPopTopCommand_Fixture_P, PopTopCommand) {

  std::stringstream commandStream(testData.input);
  auto expectedCommand = testData.commands.begin();

  while (auto command = ::RoverCpp::Rover::StringStreamRoverDecoder::popTopCommand(commandStream)) {
    EXPECT_EQ((*command), (*expectedCommand));
    ++expectedCommand;
  }

  EXPECT_EQ(expectedCommand, testData.commands.end());
}


/*
 * \description   this Ut test the correct interpretation of the calibration input
 *
 * \init
 *
 * \testAction
 *
 * \testResult
 *
 */
TEST(Decoding, Calibration) {

  const std::vector<std::pair<std::string, ::RoverCpp::Rover::RoverStateType>> testData = {
      {{"1 2 N"}, {1, 2, ::RoverCpp::Orientation::NORTH}},
      {{"-2 -2 E"}, {-2, -2, ::RoverCpp::Orientation::EAST}},
      {{"500 0 S"}, {500, 0, ::RoverCpp::Orientation::SOUTH}},
      {{"10000 100 W"}, {10000, 100, ::RoverCpp::Orientation::WEST}}};

  for (auto &test : testData) {
    auto Input = std::stringstream(test.first);
    auto Result = ::RoverCpp::Rover::StringStreamRoverDecoder::decodeCalibrationInput(Input);
    EXPECT_EQ(test.second, Result);
  }
}
} // namespace Rover
} // namespace RoverCpp
} // namespace test
