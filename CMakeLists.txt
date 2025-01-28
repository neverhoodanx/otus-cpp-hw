cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")

set(PROJECT_VESRION 1.1.${PATCH_VERSION})

project(join_server VERSION ${PROJECT_VESRION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)

configure_file(version.h.in version.h)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(${PROJECT_NAME}_SRC src/hw01_version/lib_version.cpp include/hw01_version/lib_version.hpp
                        include/hw11_join_server/join_server.hpp
                        src/hw11_join_server/join_server.cpp
                        src/hw11_join_server/join_session.cpp
                        src/hw11_join_server/join_session.hpp
                        src/hw11_join_server/table_keeper.cpp
                        src/hw11_join_server/table_keeper.hpp
                        src/hw11_join_server/table_data.hpp )
                        
add_executable(${PROJECT_NAME} main.cpp)

add_library(${PROJECT_NAME}_lib STATIC ${${PROJECT_NAME}_SRC})


set_target_properties(${PROJECT_NAME}_cli ${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(${PROJECT_NAME}_lib
    PRIVATE 
        ${CMAKE_BINARY_DIR}
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/include/hw01_version
        ${CMAKE_SOURCE_DIR}/include/hw11_join_server
)

target_include_directories(${PROJECT_NAME}_lib
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${PROJECT_NAME}_lib
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${Boost_LIBRARIES}
)

set_target_properties(${PROJECT_NAME}_lib PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
)

target_link_libraries(${PROJECT_NAME}_lib PRIVATE
    ${Boost_LIBRARIES}
)

target_include_directories(${PROJECT_NAME}_lib PRIVATE ${Boost_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR})

if(WITH_BOOST_TEST)
    add_executable(test_version 
                                tests/test_hw1_version.cpp
                                tests/test_hw11_join_server.cpp)

    set_target_properties(test_version PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    set_target_properties(test_version PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )

    target_link_libraries(test_version
        ${PROJECT_NAME}_lib
        ${Boost_LIBRARIES}
    )

    set_target_properties(${PROJECT_NAME}_lib PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK)
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
