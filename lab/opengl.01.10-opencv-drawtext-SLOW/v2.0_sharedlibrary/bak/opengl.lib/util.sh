#!/bin/bash

function my_make(){
    local out="build"
    if [ "$#" -lt 1 ]; then
        printf 'my_make:: use default value\n'
    else    
        out=$1
    fi
    printf 'my_make:: out = %s\n' "${out}"

    set -e     # stop script and exit the terminal when got any error
    set -x 
    # pushd bin 
    pushd "${out}"
    make clean
    make
    popd
    set +e
    set +x 
}

function build(){
    local out="build"
    if [ "$#" -lt 1 ]; then
        printf 'build:: use default value\n'
    else    
        out=$1
    fi
    printf 'build:: out = %s\n' "${out}"

    set -e     # stop script and exit the terminal when got any error
    set -x 
    local PROJECT_PATH=`realpath ./`

    
    mkdir "${out}"
    pushd "${out}"
    cmake -DUSER_DEFINED_BUILD_DIRECTORY="${out}" .. && make

    popd
    set +e
    set +x 
}

function clean(){
    local out="build"
    if [ "$#" -lt 1 ]; then
        printf 'clean:: use default value\n'
    else    
        out=$1
    fi
    printf 'clean:: out = %s\n' "${out}"

    set -e     # stop script and exit the terminal when got any error
    set -x 
    local PROJECT_PATH=`realpath ./`

    printf "Remove folders"
    rm -fr ./"${out}"

    set +e
    set +x 
}

