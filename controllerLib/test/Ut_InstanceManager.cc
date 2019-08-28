#include "Ut_InstanceManager_Fixture.hpp"

namespace test {
namespace RoverCpp {
namespace Controller {

using ::testing::_;
using ::testing::Return;
using ::testing::ReturnRefOfCopy;

struct IsCollisionTestType {
  MockInstanceType::StateType predictedState;
  int currentInstanceIndex;

  int expectedCollisionIndex; // set to 4 if end iter is expected
};
using InstanceManagerCollisionFixture_P = Ut_InstanceManager_Fixture<IsCollisionTestType>;

// clang-format off
const std::vector<IsCollisionTestType> IsCollisionTetsData = {
    {MockInstanceType::STATE1, 0, 4},
    {MockInstanceType::STATE1, 1, 0},
    {MockInstanceType::STATE1, 2, 0},
    {MockInstanceType::STATE1, 3, 0},
    {MockInstanceType::STATE2, 0, 1},
    {MockInstanceType::STATE2, 1, 4},
    {MockInstanceType::STATE2, 2, 1},
    {MockInstanceType::STATE2, 3, 1},
    {MockInstanceType::STATE3, 0, 2},
    {MockInstanceType::STATE3, 1, 2},
    {MockInstanceType::STATE3, 2, 4},
    {MockInstanceType::STATE3, 3, 2},
    {MockInstanceType::STATE4, 0, 3},
    {MockInstanceType::STATE4, 1, 3},
    {MockInstanceType::STATE4, 2, 3},
    {MockInstanceType::STATE4, 3, 4},
    };
// clang-format on
INSTANTIATE_TEST_CASE_P(/**/, InstanceManagerCollisionFixture_P, ::testing::ValuesIn(IsCollisionTetsData));

/*
 * \description   This Ut test the collision detection
 *
 * \init          instantiate the InstanceManager and advance its iterator for the current element
 *                by the currentInstanceIndex defined in IsCollisionTestData. Set the states of
 *                the 4 instances to STATE1... STATE4 respectively. Set behaviour of the
 *                MockConstraints::isCollision to return always false except if both arguments are
 *                the predictedState
 *
 * \testAction    call findCollision
 *
 * \testResult    the found element shall be expectedCollisionIndex_th instance. If index
 *                given as 4, end iterator is expected.
 */
TEST_P(InstanceManagerCollisionFixture_P, findCollision) {

  // init
  ASSERT_EQ(instance_manager.current_, instance_manager.instances_.begin());
  std::advance(instance_manager.current_, testData.currentInstanceIndex);

  EXPECT_CALL(mockedInstances[0], getState).WillRepeatedly(ReturnRefOfCopy(MockInstanceType::STATE1));
  EXPECT_CALL(mockedInstances[1], getState).WillRepeatedly(ReturnRefOfCopy(MockInstanceType::STATE2));
  EXPECT_CALL(mockedInstances[2], getState).WillRepeatedly(ReturnRefOfCopy(MockInstanceType::STATE3));
  EXPECT_CALL(mockedInstances[3], getState).WillRepeatedly(ReturnRefOfCopy(MockInstanceType::STATE4));

  EXPECT_CALL(mockedConstraints, isCollision(_, _)).WillRepeatedly(Return(false));
  EXPECT_CALL(mockedConstraints, isCollision(testData.predictedState, testData.predictedState)).WillRepeatedly(Return(true));

  // testAction
  const auto result = instance_manager.findCollision(testData.predictedState);

  // testResult
  auto expectedResult = mockedInstances.begin();
  std::advance(expectedResult, testData.expectedCollisionIndex);
  EXPECT_EQ(result, expectedResult);
}

struct IsInBoundTestType {
  bool constrainChecker_IsInBound;
  bool expectedResult;
};

using Ut_InstanceManager_IsInBound_P = Ut_InstanceManager_Fixture<IsInBoundTestType>;

std::vector<IsInBoundTestType> IsInBoundTestData = {
    {true, true},
    {false, false},
};

INSTANTIATE_TEST_CASE_P(/* empty prefix */, Ut_InstanceManager_IsInBound_P, testing::ValuesIn(IsInBoundTestData));

/*
 * \description   This test verifies, that the bound check call is
 *                correctly delegated to the ConstraintType
 *
 * \init          instantiate the InstanceManager
 *
 * \testAction    call isInBound
 *
 * \testResult    isInBound from the ConstraintType shall be exclusively called
 *                with the same parameter as the call was by the testAction
 *
 */
TEST_P(Ut_InstanceManager_IsInBound_P, IsInBound) {
  // testResult 1
  EXPECT_CALL(mockedConstraints, isInBound(_)).Times(0);
  EXPECT_CALL(mockedConstraints, isInBound(MockInstanceType::STATE1)).WillRepeatedly(Return(testData.constrainChecker_IsInBound));

  // testAction
  const auto result = instance_manager.isInBound(MockInstanceType::STATE1);

  // testResult 2
  EXPECT_EQ(result, testData.expectedResult);
}

/*
 * \description   This ut test if the next method correctly iterates over
 *                the InstanceManagers instances_ vector in a circle
 *
 * \init          instantiate the InstanceManager
 *
 * \testAction    call next
 *
 * \testResult    for every call to, the current_ iterator must advance by one.
 *                If end, current must be set to begin
 *
 */
TEST(Ut_InstanceManager, next) {

  InstanceManagerWithMocks instance_manager;

  EXPECT_EQ(instance_manager.current_, instance_manager.instances_.begin());
  for (int i = 1; i < 10; ++i) {
    // testAction
    instance_manager.next();

    // testResult
    auto expectedIter = instance_manager.instances_.begin();
    std::advance(expectedIter, (i % 4));
    EXPECT_EQ(instance_manager.current_, expectedIter);
  }
}

/*
 * \description   This ut test if the call to setBoundaries is correctly delgated
 *                to the ConstraintType instance
 *
 * \init          instantiate the InstanceManager
 *
 * \testAction    call setBoundaries with set parameters
 *
 * \testResult    ConstraintType::setBoundaries must be called once with the same
 *                parameters
 *
 */
TEST(Ut_InstanceManager, setBoundaries) {
  // init
  InstanceManagerWithMocks instance_manager;

  // testResult
  EXPECT_CALL(instance_manager.constraint_checker_, setBoundaries(4, 2)).Times(1);

  // testAction
  instance_manager.setBoundaries(4, 2);
}

TEST(Ut_InstanceManager, forwardCommandToCurrentInstance) {
  InstanceManagerWithMocks instance_manager;

  ASSERT_EQ(instance_manager.current_, instance_manager.instances_.begin());
  EXPECT_CALL(instance_manager.instances_[0], getId()).WillRepeatedly(ReturnRefOfCopy(std::string("ROVR_1")));
  EXPECT_CALL(instance_manager.instances_[1], getId()).WillRepeatedly(ReturnRefOfCopy(std::string("ROVR_2")));
  // EXPECT_CALL(instance_manager.instances_[2], getId()).WillRepeatedly(ReturnRefOfCopy(std::string("ROVR_3")));
  // EXPECT_CALL(instance_manager.instances_[3], getId()).WillRepeatedly(ReturnRefOfCopy(std::string("ROVR_4")));

  EXPECT_CALL(instance_manager.instances_[0], estimateState(_)).WillRepeatedly(ReturnRefOfCopy(MockInstanceType::STATE2));

  // 1. not in bound
  EXPECT_CALL(instance_manager.constraint_checker_, isInBound(_)).WillOnce(Return(false));
  EXPECT_CALL(instance_manager.instances_[0], executeCommand(_)).Times(0);

  instance_manager.forwardCommandToCurrentInstance(MockInstanceType::CMD1);

  // 2. in bound but with collision
  EXPECT_CALL(instance_manager.constraint_checker_, isInBound(_)).WillOnce(Return(true));

  EXPECT_CALL(instance_manager.instances_[0], getState).WillRepeatedly(ReturnRefOfCopy(MockInstanceType::STATE1));
  EXPECT_CALL(instance_manager.instances_[1], getState).WillRepeatedly(ReturnRefOfCopy(MockInstanceType::STATE2));
  EXPECT_CALL(instance_manager.instances_[2], getState).WillRepeatedly(ReturnRefOfCopy(MockInstanceType::STATE3));
  EXPECT_CALL(instance_manager.instances_[3], getState).WillRepeatedly(ReturnRefOfCopy(MockInstanceType::STATE4));

  EXPECT_CALL(instance_manager.constraint_checker_, isCollision(_, _)).WillRepeatedly(Return(false));
  EXPECT_CALL(instance_manager.constraint_checker_, isCollision(MockInstanceType::STATE2, MockInstanceType::STATE2))
      .WillRepeatedly(Return(true));

  EXPECT_CALL(instance_manager.instances_[0], executeCommand(_)).Times(0);

  instance_manager.forwardCommandToCurrentInstance(MockInstanceType::CMD1);

  // 3. in bound and no collisions
  EXPECT_CALL(instance_manager.constraint_checker_, isInBound(_)).WillOnce(Return(true));

  EXPECT_CALL(instance_manager.instances_[0], getState).WillRepeatedly(ReturnRefOfCopy(MockInstanceType::STATE1));
  EXPECT_CALL(instance_manager.instances_[1], getState).WillRepeatedly(ReturnRefOfCopy(MockInstanceType::STATE2));
  EXPECT_CALL(instance_manager.instances_[2], getState).WillRepeatedly(ReturnRefOfCopy(MockInstanceType::STATE3));
  EXPECT_CALL(instance_manager.instances_[3], getState).WillRepeatedly(ReturnRefOfCopy(MockInstanceType::STATE4));

  EXPECT_CALL(instance_manager.constraint_checker_, isCollision(_, _)).WillRepeatedly(Return(false));

  EXPECT_CALL(instance_manager.instances_[0], executeCommand(MockInstanceType::CMD1))
      .Times(1)
      .WillOnce(ReturnRefOfCopy(MockInstanceType::STATE2));

  instance_manager.forwardCommandToCurrentInstance(MockInstanceType::CMD1);

}
} // namespace Controller
} // namespace RoverCpp
} // namespace test