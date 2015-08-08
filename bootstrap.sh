#!/bin/sh

set -x

git submodule update --init --recursive

PWD=`pwd`
THIRD_PARTY=${PWD}/third_party

# build muduo

cd ${THIRD_PARTY}/muduo

SOURCE_DIR=`pwd`
BUILD_DIR=${BUILD_DIR:-../build}
BUILD_TYPE=${BUILD_TYPE:-release}
INSTALL_DIR=${INSTALL_DIR:-../../}
BUILD_NO_EXAMPLES=${BUILD_NO_EXAMPLES:-1}

mkdir -p $BUILD_DIR/$BUILD_TYPE && \
cd $BUILD_DIR/$BUILD_TYPE && \
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
      -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR \
      -DCMAKE_BUILD_NO_EXAMPLES=$BUILD_NO_EXAMPLES \
      $SOURCE_DIR && \
make $* && make install

# build http-parser

cd ${THIRD_PARTY}/http-parser
make && make install PREFIX=../

# build rapidjson

cd ${THIRD_PARTY}/rapidjson
mkdir -p build && \
cd build && \
cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR .. && \
make && make install
