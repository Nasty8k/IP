cmake_minimum_required(VERSION 3.5)

# Set the project name
project (sublibrary_Lab1)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Add a library with the above sources
add_library(${PROJECT_NAME} src/Lab1.cpp)
add_library(sub::lib_Lab1 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
