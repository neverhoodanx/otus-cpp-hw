include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)

target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(gtest_version test_version.cpp)

target_link_libraries(gtest_version
  PRIVATE
    GTest::GTest
    helloworld)


if (MSVC)
  target_compile_options(gtest_version PRIVATE
    /W4
  )
else ()
  target_compile_options(gtest_version PRIVATE
    -Wall -Wextra -pedantic -Werror
  )
endif()

add_test(gtest_version gtest_version)