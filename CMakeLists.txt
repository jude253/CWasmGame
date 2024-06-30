# Following SDL2 CMakeLists.txt: https://github.com/libsdl-org/SDL/blob/288aea3b40faf882f26411e6a3fe06329bba2c05/CMakeLists.txt
if(${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_BINARY_DIR})
  message(FATAL_ERROR "Prevented in-tree build. Please create a build directory outside of the source code and run `cmake ..` (path to project root) from there.")
endif()

cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(CWasmGame VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# Copied mainly from here: https://github.com/kripken/ammo.js/blob/1ed8b58c7058a5f697f2642ceef8ee20fdd55e10/CMakeLists.txt
# Following guidance from here: https://emscripten.org/docs/compiling/Building-Projects.html#examples-test-code
# Maybe copy approach from here too: https://github.com/adevaykin/minimal-cmake-emscripten-project/blob/97de429e84eb4d83072bdc84997ad07c7b82e4ad/CMakeLists.txt
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

message("CMAKE_CURRENT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message("CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")

# Some of these variables are not used and were copy and pasted from other `CMakeLists.txt`.  Leaving them in case needed in future.
FIND_PACKAGE(Python3)
set(PYTHON                ${Python3_EXECUTABLE}                                           CACHE STRING "PYTHON")
set(PROJECT_ROOT_DIR      ${PROJECT_SOURCE_DIR}                                           CACHE STRING "PROJECT_ROOT_DIR")
set(BUILD_ROOT_DIR        ${CMAKE_CURRENT_BINARY_DIR}                                     CACHE STRING "BUILD_ROOT_DIR")
set(DIST_DIR              ${BUILD_ROOT_DIR}/dist                                          CACHE STRING "DIST_DIR")
set(EMSDK_ROOT_DIR        ${PROJECT_ROOT_DIR}/include/emsdk                               CACHE STRING "EMSDK_ROOT_DIR")
set(EMSCRIPTEN_ROOT_DIR   ${EMSDK_ROOT_DIR}/upstream/emscripten                           CACHE STRING "EMSCRIPTEN_ROOT_DIR")
set(EMCC                  ${EMSCRIPTEN_ROOT_DIR}/emcc                                     CACHE STRING "EMCC")
set(CMAKE_TOOLCHAIN_FILE  ${EMSCRIPTEN_ROOT_DIR}/cmake/Modules/Platform/Emscripten.cmake  CACHE STRING "CMAKE_TOOLCHAIN_FILE")


# # Build Release by default
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build Type")

add_custom_command(
  OUTPUT index.html index.js index.wasm
  COMMAND rm -rf ${DIST_DIR}
  COMMAND mkdir  ${DIST_DIR}
  COMMAND ${EMCC} ${PROJECT_ROOT_DIR}/src/main.cpp --use-port=sdl2 -o ${DIST_DIR}/index.html
  VERBATIM
)
add_custom_target(CWasmGame ALL DEPENDS index.html index.js index.wasm)

set_property(TARGET CWasmGame PROPERTY CXX_STANDARD 11)
