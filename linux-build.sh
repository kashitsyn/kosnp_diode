#!/bin/bash

set -eu

BUILD_DIR="$PWD/build/linux"
INSTALL_DIR="$PWD/install"
rm -rf "$BUILD_DIR"   && mkdir -p "$BUILD_DIR"
rm -rf "$INSTALL_DIR" && mkdir -p "$INSTALL_DIR"

cd "$BUILD_DIR"
cmake \
  -DCMAKE_INSTALL_PREFIX="$INSTALL_DIR" \
  -DCMAKE_INSTALL_RPATH_USE_LINK_PATH=ON \
  -DCMAKE_C_FLAGS="-g" \
  -DCMAKE_CXX_FLAGS="-g" \
  ../..

cmake --build . --target install

"$INSTALL_DIR"/bin/Diode
