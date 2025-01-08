#!/bin/bash
. ./util.sh

function main(){
    local target="../test"
    local build="build"
    if [ "$#" -lt 1 ]; then
        printf 'main:: use default value\n'
    else    
        build=$1
    fi
    printf 'main:: build = %s\n' "${build}"

    
    if test -d ${target}; then
        printf "copy to *.sh to the ${target}.\n"
        cp ${build}/*.so* ${target}
    else
        printf "${target} does not exist.\n"
        return -1
    fi
}

main
