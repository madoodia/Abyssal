# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #

#!/usr/bin/env bash

# Running:
# ./build.sh
# or
# open in vscode and run Alt+Ctrl+B


BASEDIR=$(dirname "$0")
export TARGET_NAME=$(basename $BASEDIR)

# Qt5 cmake config
export Qt5_DIR=$SDKS_LOCATION/Qt5/lib/cmake

# GLEW
export GLEW_LOCATION=$SDKS_LOCATION/glew

# STB_IMAGE
export STB_LOCATION=$SDKS_LOCATION/stb

# GLM
export GLM_LOCATION=$SDKS_LOCATION/glm

# echo $TARGET_NAME

mkdir -p build
cd build

cmake -G "Unix Makefiles" -DCMAKE_PREFIX_PATH=$GLEW_LOCATION ..
cmake --build .

cp src/$TARGET_NAME ../
cd ..

echo ""
echo "======================"
echo ""

# rm -rf build

./$TARGET_NAME