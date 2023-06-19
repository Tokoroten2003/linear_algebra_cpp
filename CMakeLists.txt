cmake_minimum_required(VERSION 3.14)
project(mcalc)

add_library(marith INTERFACE)
target_include_directories(marith
  INTERFACE
    ${CMAKE_SOURCE_DIR}/include
)
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(marith_test test/marith_test.cpp)
target_link_libraries(marith_test
  gtest_main
  marith
)
add_test(NAME marith_test COMMAND marith_test)

include(GoogleTest)
gtest_discover_tests(marith_test)