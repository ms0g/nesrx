cmake_minimum_required(VERSION 3.17.0)
project(nesrx VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES "src/*")

add_executable(${PROJECT_NAME} ${SOURCES})
