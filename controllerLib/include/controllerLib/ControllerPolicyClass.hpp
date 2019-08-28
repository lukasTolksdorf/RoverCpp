#ifndef ROVERCPP_CONTROLLERLIB_STRING_STREAM_CONTROLLER_HPP_
#define ROVERCPP_CONTROLLERLIB_STRING_STREAM_CONTROLLER_HPP_

#include "TestUtils.hpp"

namespace RoverCpp {
namespace Controller {

template <class CommandDecoder, class InstanceManager> class Controller_PolicyClass {
public:
  Controller_PolicyClass() : instance_manager_(){};

  template < typename... Args>
  void processCalibrationInput(Args&... inputs_) {
    auto calibrationValue = CommandDecoder::decodeCalibrationInput(inputs_...);
    instance_manager_.calibrateCurrentInstance(calibrationValue);
  }

  // #todo allow for the usage of rvalues for inputs (e.g. by moving)
  template <typename... Args>
  void processCommands(Args& ...inputs_) {
    while (auto command = CommandDecoder::popTopCommand(inputs_...)) {
      instance_manager_.forwardCommandToCurrentInstance(*command);
    }
  }

  void nextInstance() { instance_manager_.next(); }

  template <typename... Args> void setBoundaries(const Args &... args) { instance_manager_.setBoundaries(args...); }

PRIVATE:
  InstanceManager instance_manager_;
};

} // namespace Controller
} // namespace RoverCpp

#endif // ROVERCPP_CONTROLLERLIB_STRING_STREAM_CONTROLLER_HPP_
