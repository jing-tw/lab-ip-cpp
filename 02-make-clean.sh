#!/bin/bash
function main() {
    set -e     # stop script and exit the terminal when got any error
    set -x 
    local PROJECT_PATH=`realpath ./project`

    echo "Remove related libraries"
    rm -fr	./FFmpeg ./build ./opencv ./opencv_build ./opencv_contrib

    echo "Remove ncnn  source, include and library"
    rm -fr ./ncnn
    rm -fr "$PROJECT_PATH"/include/nn/ncnn
    rm -fr "$PROJECT_PATH"/lib/cmake  "$PROJECT_PATH"/lib/ncnn.a "$PROJECT_PATH"/lib/pkgconfig

    set +e
    set +x 
}

main
