#!/bin/bash
function main() {
    set -e     # stop script and exit the terminal when got any error
    set -x 
    local PROJECT_PATH=`realpath ./`
    
    cmake ./ && make	
    set +e
    set +x 
}

main
