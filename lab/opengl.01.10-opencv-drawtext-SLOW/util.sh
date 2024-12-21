#!/bin/bash
function build(){
    set -e     # stop script and exit the terminal when got any error
    set -x 
    local PROJECT_PATH=`realpath ./`
    
    mkdir bin
    pushd bin
    cmake .. && make

    popd
    set +e
    set +x 
}

function clean(){
    set -e     # stop script and exit the terminal when got any error
    set -x 
    local PROJECT_PATH=`realpath ./`

    echo "Remove folders"
    rm -fr ./bin

    set +e
    set +x 
}

