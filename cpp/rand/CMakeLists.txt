project(cppdemo)
cmake_minimum_required(VERSION 3.0)

set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_EXTENSIONS ON )
set( CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp)
