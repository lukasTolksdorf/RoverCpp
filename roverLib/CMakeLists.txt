add_library_without_mut(roverLib
        include/roverLib/Rover.hpp
        include/roverLib/RoverConstraints.hpp
        include/roverLib/StringStreamRoverDecoder.hpp
        src/Rover.cc
        src/RoverConstraints.cc
        src/StringStreamRoverDecoder.cc
)

# Needed for compiler warning settings, even if no other lib is linked
target_link_libraries_without_mut(roverLib)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTS)
    add_subdirectory(test)
endif()
