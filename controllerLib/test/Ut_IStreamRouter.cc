#include "Ut_IStreamRouter_Fixture.hpp"

namespace test {
namespace RoverCpp {
namespace Controller {

using ::testing::_;
using ::testing::InSequence;

/*
 * \description   This ut test if the IStreamRouter splits the input into
 *                the correct peaches and delegates it to the correct
 *                method from the controller
 *
 * \init          instantiate the IStreamRouter with a mocked controller as
 *                well as the input stream
 *
 * \testAction    call processInputStream with the input stream
 *
 * \testResult    the correct parts of the stream must be delegated
 *                to the correct method of the controller
 */
TEST_F(Ut_IStreamRouter_Fixture, generalRouting) {
  auto inputStream = std::stringstream("3 31\n"
                                       "1 2 N\n"
                                       "ABSDFASDF\n"
                                       "3 4 S\n"
                                       "ABCDEFG\n"
                                       "5 6 E\n"
                                       "HIJKL\n"
                                       "7 8 W\n"
                                       "MNOPQRS\n"
                                       "9 10 N\n"
                                       "TUVWXYZ");

  {
    // testResult
    InSequence seq;
    EXPECT_CALL(mocked_controller, setBoundaries(3, 31)).Times(1);

    EXPECT_CALL(mocked_controller, processCalibrationInput(SStreamMatchesString("1 2 N"))).Times(1);
    EXPECT_CALL(mocked_controller, processCommands(SStreamMatchesString("ABSDFASDF"))).Times(1);
    EXPECT_CALL(mocked_controller, nextInstance()).Times(1);

    EXPECT_CALL(mocked_controller, processCalibrationInput(SStreamMatchesString("3 4 S"))).Times(1);
    EXPECT_CALL(mocked_controller, processCommands(SStreamMatchesString("ABCDEFG"))).Times(1);
    EXPECT_CALL(mocked_controller, nextInstance()).Times(1);

    EXPECT_CALL(mocked_controller, processCalibrationInput(SStreamMatchesString("5 6 E"))).Times(1);
    EXPECT_CALL(mocked_controller, processCommands(SStreamMatchesString("HIJKL"))).Times(1);
    EXPECT_CALL(mocked_controller, nextInstance()).Times(1);

    EXPECT_CALL(mocked_controller, processCalibrationInput(SStreamMatchesString("7 8 W"))).Times(1);
    EXPECT_CALL(mocked_controller, processCommands(SStreamMatchesString("MNOPQRS"))).Times(1);
    EXPECT_CALL(mocked_controller, nextInstance()).Times(1);

    EXPECT_CALL(mocked_controller, processCalibrationInput(SStreamMatchesString("9 10 N"))).Times(1);
    EXPECT_CALL(mocked_controller, processCommands(SStreamMatchesString("TUVWXYZ"))).Times(1);
    EXPECT_CALL(mocked_controller, nextInstance()).Times(1);
  }
  // testAction
  router_instance.processInputStream(inputStream);
}
} // namespace Controller
} // namespace RoverCpp
}