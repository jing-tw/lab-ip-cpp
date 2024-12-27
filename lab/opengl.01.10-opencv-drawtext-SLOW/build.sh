#!/bin/bash
. ./util.sh

# Check if the ./bin directory exists
if [ ! -d "./bin" ]; then
    # If it does not exist, invoke the build command
    echo "./bin does not exist. Invoking build..."
    build  # Replace 'build' with the actual command to invoke your build process
else
    # If it exists, run make
    echo "./bin exists. Running make..."
    my_make
fi

