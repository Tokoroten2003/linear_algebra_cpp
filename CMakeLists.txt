cmake_minimum_required(VERSION 3.13)

project(mcalc CXX)

add_executable(test_Marith
    test/test_Marith.cpp
)

add_executable(test_SqMarith
    test/test_SqMarith.cpp
)

target_link_libraries(test_Marith matrix)
target_link_libraries(test_SqMarith matrix)

add_library(matrix INTERFACE)

target_include_directories(matrix
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
