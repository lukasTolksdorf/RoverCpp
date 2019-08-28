#ifndef ROVERCPP_CONTROLLERLIB_INSTANCEMANANGER_HPP_
#define ROVERCPP_CONTROLLERLIB_INSTANCEMANANGER_HPP_

#include "controllerLib/TestUtils.hpp"
#include "TestUtils.hpp"

#include <array>
#include <fstream>
#include <iostream>
#include <string>

namespace RoverCpp {
namespace Controller {

template <class InstanceType, class ConstraintType> class InstanceManager {
public:
  InstanceManager() : instances_(), current_(instances_.begin()) {
    logStream_.open("RoverController.log");
    if (!logStream_) {
      std::cerr << "Error: file \"RoverController.log\" could no be opened!\n";
      throw std::runtime_error("log file blocked");
    }
  }

  ~InstanceManager() { logStream_.close(); }

  void next() {
    ++current_;
    if (instances_.end() == current_) {
      current_ = instances_.begin();
    }
  }

  template <class... Args> void setBoundaries(const Args &... args) { constraint_checker_.setBoundaries(args...); }

  void forwardCommandToCurrentInstance(typename InstanceType::CommandType command_) {
    const auto predictedState = current_->estimateState(command_);
    if (!isInBound(predictedState)) {
      std::string msg = "command [" + std::to_string(static_cast<int>(command_)) + "] would violate the boundaries -> command ignored!";
      log(current_->getId(), msg);
      return;
    }
    auto crashIter = findCollision(predictedState);
    if (instances_.end() != crashIter) {
      std::string msg = "command [" + std::to_string(static_cast<int>(command_)) + "] would result in a crash with " + crashIter->getId() +
                        " -> command ignored!";
      log(current_->getId(), msg);
    } else {
      auto newState = current_->executeCommand(command_);
      logState(current_->getId(), newState);
    }
  }

  void calibrateCurrentInstance(const typename InstanceType::StateType &state_) {
    if (current_->wasCalibrated()) {
      log(current_.getId(), "was recalibrated!");
    }
    current_->calibrate(state_);
  }
  
PRIVATE:

  std::array<InstanceType, 4> instances_;
  typename std::array<InstanceType, 4>::iterator current_;
  ConstraintType constraint_checker_;
  std::ofstream logStream_;

  bool isInBound(const typename InstanceType::StateType &state_) const { return constraint_checker_.isInBound(state_); }

  auto findCollision(const typename InstanceType::StateType &state_) const {
    for (auto iter = instances_.begin(); iter != instances_.end(); ++iter) {
      if (iter != current_ && constraint_checker_.isCollision(iter->getState(), state_)) {
        return iter;
      }
    }
    return instances_.end();
  };

  void log(const std::string &instanceId_, const std::string &msg_) { logStream_ << "[" << instanceId_ << "] " << msg_ << "\n"; }

  void logState(const std::string &instanceId_, const typename InstanceType::StateType &state_) {
    logStream_ << "[" << instanceId_ << "] state: " << state_ << "\n";
  }
};

} // namespace Controller
} // namespace RoverCpp

#endif // ROVERCPP_CONTROLLERLIB_INSTANCEMANANGER_HPP_