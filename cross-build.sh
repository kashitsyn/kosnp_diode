#!/bin/bash

set -eu

QEMU_FLAGS+=(-nic "user,ipv6=off,net=192.168.188.0/24,host=192.168.188.1,hostfwd=tcp::5000-192.168.188.8:5000")
QEMU_FLAGS+=(-nographic -monitor "telnet:localhost:4444,server,nowait")

BUILD_DIR="$PWD/build/qemu"
rm -rf "$BUILD_DIR" && mkdir -p "$BUILD_DIR"

export TARGET="arm-kos"
export PKG_CONFIG=""
export SDK_PREFIX="/opt/KasperskyOS-Community-Edition-1.0.1.4" # NOTE: Change variable if your SDK version is different.
BUILD_SIM_TARGET="y"
export PATH="$SDK_PREFIX/toolchain/bin:$PATH"

cd "$BUILD_DIR"
cmake \
  -DCMAKE_TOOLCHAIN_FILE="$SDK_PREFIX/toolchain/share/toolchain-arm-kos.cmake" \
  -DCMAKE_C_FLAGS="-g" \
  -DCMAKE_CXX_FLAGS="-g" \
  -DDEMO_QEMU_FLAGS="${QEMU_FLAGS[*]}" \
  ../.. && make sim
