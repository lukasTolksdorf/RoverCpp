#todo extend with second target which includes everything as public for linking with Ut targets

macro(add_testable_library name)
    add_library(${name} ${ARGN}
    )

    target_include_directories(${name} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src
    )

    set_property(TARGET ${name} PROPERTY CXX_STANDARD 14)
endmacro()

macro(testable_target_link_libraries name)
    target_link_libraries(${name} ${ARGN} project_warnings)
endmacro()
