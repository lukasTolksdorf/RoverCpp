#include "MockInstanceType.hpp"
#include "Ut_ControllerPolicyClass_Fixture.hpp"

#include "gtest/gtest.h"

#include <sstream>

namespace test {
namespace RoverCpp {
namespace Controller {

using ::testing::_;

/*
 * \description   tests if the decoded calibration input is correctly delegated
 *                to the InstanceManager. Due to time limitations, a FakeCommandDecoder
 *                was used instead of a proper mock object
 *
 *  \init         instantiate the Controller instance
 *
 *  \testAction   call processCalibrationInput
 *
 *  \testResult   the instance manager instance recieves the decoded state from
 *                the fake decoder
 */
TEST_F(Ut_ControllerPolicyClass_Fixture, processCallibrationInput) {

  EXPECT_CALL(controller.instance_manager_, calibrateCurrentInstance(MockInstanceType::STATE4)).Times(1);

  auto input = std::stringstream("1 2 N");
  controller.processCalibrationInput(input);
}

/*
 * \description   tests if the decoded command is routed correctly to the instance manager
 *                as long as a valid command is decoded. due to time limitation, a fake object
 *                was used for the decoder, which always returns one CMD3 and next a nullopt
 *
 *  \init         instantiate the Controller instance
 *
 *  \testAction   call processCommands
 *
 *  \testResult   the instance manager instance receives the state from the fake decoder
 */
TEST_F(Ut_ControllerPolicyClass_Fixture, popTopCommand) {
  EXPECT_CALL(controller.instance_manager_, forwardCommandToCurrentInstance(_)).Times(0);
  EXPECT_CALL(controller.instance_manager_, forwardCommandToCurrentInstance(MockInstanceType::CMD3)).Times(1);

  auto input = std::stringstream("ABC");
  controller.processCommands(input);
}

/*
 * \description   test if the setBoundaries and nextInstance call are routed correctly
 *
 * \init          instantiate the Controller instance
 *
 * \testAction    call setBoundaries with given parameters and nextInstance
 *
 * \testResult    both call shall be received by the instance manager
 */
TEST_F(Ut_ControllerPolicyClass_Fixture, setBoundariesAndNextInstance) {
  EXPECT_CALL(controller.instance_manager_, setBoundaries(_,_)).Times(0);
  EXPECT_CALL(controller.instance_manager_, setBoundaries(-1, 99)).Times(1);

  controller.setBoundaries(-1, 99);

  EXPECT_CALL(controller.instance_manager_, next).Times(1);

  controller.nextInstance();
}
} // namespace Controller
} // namespace RoverCpp
} // namespace test
