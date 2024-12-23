cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")

set(PROJECT_VESRION 0.7.${PATCH_VERSION})

project(bulk VERSION ${PROJECT_VESRION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)

configure_file(version.h.in version.h)

set(${PROJECT_NAME}_SRC src/lib.cpp include/lib.hpp
                        src/ip_filter.cpp include/ip_filter.hpp
                        include/custom_allocator.hpp
                        include/custom_vector.hpp
                        src/split.hpp
                        src/number_sequence.hpp
                        include/graphic_editor/canvas.hpp
                        include/graphic_editor/circle.hpp
                        include/graphic_editor/controller.hpp
                        include/graphic_editor/shape_manager.hpp
                        include/graphic_editor/iShape.hpp
                        src/graphic_editor/canvas.cpp
                        src/graphic_editor/circle.cpp
                        src/graphic_editor/controller.cpp
                        src/graphic_editor/shape_manager.cpp
                        include/custom_matrix.hpp
                        include/print_tuple.hpp
                        include/hw07_terminal/terminal.hpp
                        src/hw07_terminal/terminal.cpp
                        src/hw07_terminal/command_parser.cpp
                        src/hw07_terminal/command_parser.hpp
                        src/hw07_terminal/command_handler.cpp
                        src/hw07_terminal/command_handler.hpp)

add_executable(${PROJECT_NAME} main.cpp)
add_library(${PROJECT_NAME}_lib ${${PROJECT_NAME}_SRC})

set_target_properties(${PROJECT_NAME} ${PROJECT_NAME}_lib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(${PROJECT_NAME}_lib
    PRIVATE 
        ${CMAKE_BINARY_DIR}
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/include/graphic_editor
)

target_include_directories(${PROJECT_NAME}_lib
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${PROJECT_NAME}_lib

)

if(WITH_BOOST_TEST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    add_executable(test_version tests/test_hw1_version.cpp 
                                tests/test_hw2_ip_filter.cpp 
                                tests/test_hw3_custom_vector.cpp
                                tests/test_hw3_custom_allocator.cpp
                                tests/test_hw5_graphic_editor.cpp
                                tests/test_hw6_matrix.cpp
                                tests/test_hw7_terminal.cpp)

    set_target_properties(test_version PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    set_target_properties(test_version PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )

    target_link_libraries(test_version
        ${Boost_LIBRARIES}
        ${PROJECT_NAME}_lib
    )
endif()

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        /W4
    )
    target_compile_options(${PROJECT_NAME}_lib PRIVATE
        /W4
    )
    if(WITH_BOOST_TEST)
        target_compile_options(test_version PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(${PROJECT_NAME}_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_BOOST_TEST)
        target_compile_options(test_version PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT neverhooda@gmail.com)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(test_version test_version)
endif()
