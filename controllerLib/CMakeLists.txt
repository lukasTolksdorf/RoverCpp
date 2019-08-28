add_library_with_mut(controllerLib
        include/controllerLib/ControllerPolicyClass.hpp
        include/controllerLib/InstanceMananger.hpp
        include/controllerLib/IStreamRouter.hpp
        include/controllerLib/TestUtils.hpp
)

# Needed for compiler warning settings, even if no other lib is linked
target_link_libraries_with_mut(controllerLib roverLib)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTS)
    add_subdirectory(test)
endif()
