# creates a library and its mutated form for Unit Testing
macro(add_library_with_mut name)
    add_library(${name} ${ARGN}
    )

    target_include_directories(${name} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE src
    )
    set_property(TARGET ${name} PROPERTY CXX_STANDARD 14)

    add_library(${name}_mut ${ARGN})

    target_include_directories(${name}_mut PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
            PRIVATE src
            )

    target_compile_definitions(${name}_mut PUBLIC BUILD_FOR_UNITTEST)
    set_property(TARGET ${name}_mut PROPERTY CXX_STANDARD 14)
    set_target_properties(${name}_mut PROPERTIES LINKER_LANGUAGE CXX)

endmacro()

macro(target_link_libraries_with_mut name)
    target_link_libraries(${name} ${ARGN} project_warnings)
    target_link_libraries(${name}_mut ${ARGN})
endmacro()

macro(add_library_without_mut name)
    add_library(${name} ${ARGN})

    target_include_directories(${name} PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
            PRIVATE src
            )
    set_property(TARGET ${name} PROPERTY CXX_STANDARD 14)

endmacro()

macro(target_link_libraries_without_mut name)
    target_link_libraries(${name} ${ARGN} project_warnings)
endmacro()
