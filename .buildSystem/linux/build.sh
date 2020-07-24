# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #

# -----= Getting Inputs =---- #
ROOT=$1
FOLDER=$2
export FILE_NAME=$3
export TARGET_NAME=$(basename $ROOT)
# --------------------------- #

# ------= Include Envs =----- #
LINUX_DIR=$(dirname "$0")
. $LINUX_DIR/envVars.sh
# --------------------------- #

# --------- Common ---------- #
cd $ROOT
if [ -d build ]; then
    rm -rf build
fi
if [ -f "$TARGET_NAME" ]; then
    rm -rf $TARGET_NAME
fi

mkdir build
cd build

cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=$EXTRA_PREFIX_PATH $ROOT
cmake --build .

# ---= Workspace Project =--- #

cd $ROOT/build/src
cp $TARGET_NAME $ROOT

cd $ROOT
echo --------------------------------
./$TARGET_NAME

# --------------------------- #
