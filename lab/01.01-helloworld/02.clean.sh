#!/bin/bash
function main() {
    set -e     # stop script and exit the terminal when got any error
    set -x

    echo "Remove ./build"
    rm -fr ./build

    set +e
    set +x
}

main
