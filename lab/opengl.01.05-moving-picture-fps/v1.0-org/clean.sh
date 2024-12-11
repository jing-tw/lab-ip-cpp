#!/bin/bash
function main() {
    set -e     # stop script and exit the terminal when got any error
    set -x 
    local PROJECT_PATH=`realpath ./`

    echo "Remove folders"
    rm -fr "$PROJECT_PATH"/CMakeFiles
    rm -fr "$PROJECT_PATH"/CMakeCache.txt
    rm -fr "$PROJECT_PATH"/cmake_install.cmake
    rm -fr "$PROJECT_PATH"/Makefile
    rm -fr "$PROJECT_PATH"/libglad.a
    rm -fr "$PROJECT_PATH"/OpenGLDemo
    set +e
    set +x 
}

main
