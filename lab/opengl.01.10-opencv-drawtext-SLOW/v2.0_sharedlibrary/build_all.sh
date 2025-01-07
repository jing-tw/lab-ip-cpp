#!/bin/bash

function main(){
	build_library
	build_test
}

function build_library(){
    pushd opencv.lib
    ./clean.sh && ./build.sh && ./deploy.sh
    popd
    
    pushd opengl.lib
    ./clean.sh && ./build.sh && ./deploy.sh
    popd
    
    pushd opengl_opencv.lib
    ../clean.sh && ./build.sh && ./deploy.sh
    popd
}

function build_test(){
    pushd test
    ./clean.sh && ./build.sh
    popd
}


main

