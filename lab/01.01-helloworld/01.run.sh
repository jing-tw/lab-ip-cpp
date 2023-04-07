#!/bin/bash

set -e     # stop script and exit the terminal when got any error
mkdir -p build
cd build
cmake ../
make
set +e 

./test
