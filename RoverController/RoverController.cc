#include "controllerLib/ControllerPolicyClass.hpp"
#include "roverLib/Rover.hpp"
#include "roverLib/RoverConstraints.hpp"
#include "roverLib/StringStreamRoverDecoder.hpp"

#include <controllerLib/IStreamRouter.hpp>
#include <controllerLib/InstanceMananger.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
  using namespace RoverCpp;

  using RoverController = Controller::Controller_PolicyClass < Rover::StringStreamRoverDecoder,
        Controller::InstanceManager<Rover::Rover, Rover::RoverConstraints>>;

  Controller::IStreamRouter<RoverController> pipeline{};

  pipeline.processInputStream(std::cin);

  return 0;
}