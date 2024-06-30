## CWasmGame

This is a simple project to build a game for Wasm using Emscripten and CMake.  

## Dependencies:
- CMake
  - Docs: https://cmake.org/
  - Installation: https://github.com/Kitware/CMake?tab=readme-ov-file#unixmac-osxmingwmsyscygwin
- Emscripten
  - Docs: https://emscripten.org/
  - Source Code
  - Installation: https://emscripten.org/docs/getting_started/downloads.html
- SDL2
  - Docs: https://www.libsdl.org/
  - Source Code: https://github.com/libsdl-org/SDL/tree/SDL2
  - Emscripten support: https://github.com/libsdl-org/SDL/blob/main/docs/README-emscripten.md

## Initial Project Setup

```
# Clone repo and submodules:
git clone --recurse-submodules https://github.com/jude253/CWasmGame.git

# Setup up emscripten
./setup_emscripten.sh
```


## Build Commands

Make a build (doesn't have to be named `build/`) directory, run `cmake` with relative path to project root from there, then run `make`.  Somewhat like the unix style build, but with no `configure` step yet.

```
mkdir build

cd build

cmake ..

make

```

The generated output code would then be in the `./build/dist/` directory following the above commands.

I included a simple `CMakePresets.json` file in the root of this project, but I don't understand how that's supposed to be used yet.  It seems to run the `cmake` command, but not `make` command in the `./build/` directory, if you save in `CMakeLists.txt` in vscode with CMake extensions installed.  I haven't yet understood the full scope of what that can do and what it's intented for.  It seems like it could be a good way to have the compiled WASM update more automatically from saving files or something, but I am not sure how to do that or if that's really the purpose of this file yet.