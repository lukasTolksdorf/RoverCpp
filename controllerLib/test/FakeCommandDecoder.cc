#include "FakeCommandDecoder.hpp"

namespace test {
namespace RoverCpp {
namespace Controller {

FakeCommandDecoder::FakeCommandDecoder() = default;

MockInstanceType::StateType FakeCommandDecoder::decodeCalibrationInput(std::stringstream &input) { return MockInstanceType::STATE4; }

std::experimental::optional<typename MockInstanceType::CommandType> FakeCommandDecoder::popTopCommand(std::stringstream &input) {
  static bool returnedValid = false;
  if(returnedValid) {
    returnedValid = !returnedValid;
    return std::experimental::nullopt;
  } else {
    returnedValid = !returnedValid;
    return MockInstanceType::CMD3;
  }
}
} // namespace Controller
} // namespace RoverCpp
} // namespace test
