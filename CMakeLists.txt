cmake_minimum_required(VERSION 3.0.0)
project(CWasmGame VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(CWasmGame src/main.cpp)

set_property(TARGET CWasmGame PROPERTY CXX_STANDARD 17)
