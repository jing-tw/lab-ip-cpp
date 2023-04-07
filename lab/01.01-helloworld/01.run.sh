#!/bin/bash

set -e     # stop script and exit the terminal when got any error
mkdir -p build
cd build
cmake ../src
make
set +e 

./test
