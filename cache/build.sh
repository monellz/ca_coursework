#!/bin/bash

rm -rf build
mkdir build
cd build

cmake ..
make
make test
#cd test
#./replace_policy_test
