cmake_minimum_required(VERSION 3.20 FATAL_ERROR)


# Copied mainly from here: https://github.com/kripken/ammo.js/blob/1ed8b58c7058a5f697f2642ceef8ee20fdd55e10/CMakeLists.txt
# Following guidance from here: https://emscripten.org/docs/compiling/Building-Projects.html#examples-test-code
# Maybe copy approach from here too: https://github.com/adevaykin/minimal-cmake-emscripten-project/blob/97de429e84eb4d83072bdc84997ad07c7b82e4ad/CMakeLists.txt
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

FIND_PACKAGE(Python3)
set(PYTHON ${Python3_EXECUTABLE} CACHE STRING "Python path")
set(EMSDK_ROOT ./include/emsdk CACHE STRING "Emsdk path")
set(EMSCRIPTEN_ROOT ${EMSDK_ROOT}/upstream/emscripten CACHE STRING "Emscripten path")
set(CMAKE_TOOLCHAIN_FILE ${EMSCRIPTEN_ROOT}/cmake/Modules/Platform/Emscripten.cmake)
set(BUILD_DIR ./build)

# Build Release by default
set(CMAKE_BUILD_TYPE Release CACHE STRING "Build Type")

#######################################
project(CWasmGame VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

#######################################
add_custom_command(
  OUTPUT ${BUILD_DIR}
  COMMAND rm -rf ${BUILD_DIR} && mkdir ${BUILD_DIR}
  DEPENDS ${BUILD_DIR}
  VERBATIM)

add_custom_command(
  OUTPUT output.html output.js output.wasm
  COMMAND ${EMSCRIPTEN_ROOT}/emcc ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp --use-port=sdl2 -sLEGACY_GL_EMULATION -o build/output.html
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp ${BUILD_DIR}
  VERBATIM)
add_custom_target(CWasmGame ALL DEPENDS output.html output.js output.wasm)

set_property(TARGET CWasmGame PROPERTY CXX_STANDARD 11)
