#ifndef ROVERCPP_CONTROLLERLIB_ISTREAMROUTER_HPP_
#define ROVERCPP_CONTROLLERLIB_ISTREAMROUTER_HPP_

#include "TestUtils.hpp"

#include <istream>
#include <limits>
#include <sstream>

namespace RoverCpp {
namespace Controller {

template <class ControllerType> class IStreamRouter {
public:
  IStreamRouter() : controller_instance_() {
    // intentionally left empty
  }

  void processInputStream(std::istream &iStream) {
    int xLim = 0;
    int yLim = 0;
    iStream >> xLim >> yLim;
    iStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    controller_instance_.setBoundaries(xLim, yLim);

    auto route = [this, isCalibrationData = true](std::stringstream &content) mutable {
      if (isCalibrationData) {
        controller_instance_.processCalibrationInput(content);
      } else {
        controller_instance_.processCommands(content);
        controller_instance_.nextInstance();
      }
      isCalibrationData = !isCalibrationData;
    };

    while (!iStream.eof()) {
      std::string contentLine;
      std::getline(iStream, contentLine);
      auto contentLineStream = std::stringstream(contentLine);
      route(contentLineStream);
    }
  }

PRIVATE:
  ControllerType controller_instance_;
};
} // namespace Controller
} // namespace RoverCpp

#endif // ROVERCPP_CONTROLLERLIB_ISTREAMROUTER_HPP_
