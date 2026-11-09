#!/bin/bash
set -ex

# Install to conda style directories
[[ -d lib64 ]] && mv lib64 lib

mkdir -p $PREFIX/include
cp -vrp include/* $PREFIX/include/

mkdir -p $PREFIX/lib
cp -vrpd lib/* $PREFIX/lib/

# Anaconda: set the RPATH explicitly and disable conda-build's binary relocation.
# Otherwise conda-build can record the relocated size in info/paths.json while
# packaging the unrelocated binary, which makes conda report a SafetyError.
for lib in "$PREFIX"/lib/libcuest.so.*.*; do
    patchelf --force-rpath --set-rpath '$ORIGIN/.' "$lib"
done

check-glibc "$PREFIX"/lib*/*.so.*
