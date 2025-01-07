#!/bin/bash
. ./util.sh

function main(){
    local out="build"
    if [ "$#" -lt 1 ]; then
        printf 'main:: use default value\n'
    else    
        out=$1
    fi
    print 'main:: out = %s\n' "${out}"

    # Check if the ./bin directory exists
    if [ ! -d "${out}" ]; then
        # If it does not exist, invoke the build command
        echo "${out} does not exist. Invoking build..."
        build  "${out}"
    else
        # If it exists, run make
        echo "./${out} exists. Running make..."
        my_make "${out}"
    fi
}

main

