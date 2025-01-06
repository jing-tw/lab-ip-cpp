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

    clean "${out}"
}

main
