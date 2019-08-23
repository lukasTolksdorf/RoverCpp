add_testable_library(roverLib
        include/roverLib/Rover.hpp
        src/Rover.cc
)

# Needed for compiler warning settings, even if no other lib is linked
testable_target_link_libraries(roverLib)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTS)
    add_subdirectory(test)
endif()
