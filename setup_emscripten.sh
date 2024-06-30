
# Docs: https://emscripten.org/docs/getting_started/downloads.html#sdk-download-and-install

git pull

EMSDK_VERSION="3.1.61"

./include/emsdk/emsdk install $EMSDK_VERSION

./include/emsdk/emsdk activate $EMSDK_VERSION

# Use emsdk from relative path, not "source ./emsdk_env.sh" script.
