#!/bin/bash

function main(){
	clean_library
	clean_test
}

function clean_library(){
    pushd opencv.lib
    ./clean.sh
    popd
    
    pushd opengl.lib
    ./clean.sh
    popd
    
    pushd opengl_opencv.lib
    ../clean.sh
    popd
}

function clean_test(){
    pushd test
    ./clean.sh   # clean binary
    rm *.so*  # clean all deployed shared library
    popd
}



main

