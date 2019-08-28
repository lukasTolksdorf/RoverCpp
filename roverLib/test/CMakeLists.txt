add_executable(Ut_roverLib
        Ut_GenericParamTest_Fixture.hpp
        Ut_Rover.cc
        Ut_Rover_Fixture.hpp
        Ut_RoverConstraints.cc
        Ut_StringStreamRoverDecoder.cc
        )

target_link_libraries(Ut_roverLib roverLib gtest gmock gtest_main)
