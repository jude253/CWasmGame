## CWasmGame

This is a simple project to build a game for Wasm using Emscripten and CMake.  

## Dependencies:
- CMake
  - Docs: https://cmake.org/
  - Installation: https://github.com/Kitware/CMake?tab=readme-ov-file#unixmac-osxmingwmsyscygwin
- Emscripten
  - Docs: https://emscripten.org/
  - Installation: https://emscripten.org/docs/getting_started/downloads.html

## Build Commands

#### Initial Project Setup


```
# Clone repo and submodules:
git clone --recurse-submodules https://github.com/jude253/CWasmGame.git

# Setup up emscripten
./setup_emscripten.sh

# Run this on initial setup and after adjusting build scripts:
cmake .
```

#### Standard Build Command
```
cmake --build .
```