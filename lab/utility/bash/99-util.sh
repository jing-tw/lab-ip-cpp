#!/bin/bash

# util_message Show message and wait second fo nootification
# $1: string, a message for show
# $2: number, the second for wait 
# Usage: 
# util_message "==== Step 1: Build  ====" MSG_WAIT_SEC
function util_message() {
    echo $1
    util_count_down $2
}

function util_count_down() {
        local OLD_IFS="${IFS}"
        IFS=":"
        local SECONDS=$1
        local START=$(date +%s)
        local END=$((START + SECONDS))
        local CUR=$START

        while [[ $CUR -lt $END ]]
        do
                CUR=$(date +%s)
                LEFT=$((END-CUR))

                printf "\r%02d:%02d:%02d" \
                        $((LEFT/3600)) $(( (LEFT/60)%60)) $((LEFT%60))

                sleep 1
        done
        IFS="${OLD_IFS}"
        echo "        "
}


# Build the test module
function build() {
    local INSTALL_SCRIPT_PATH=`realpath ./`
    MSG_WAIT_SEC=0

    set +e     # stop script and exit the terminal when got any error
    set +x     # show command
    
    util_message "==== Build the testing module ====" MSG_WAIT_SEC
    mkdir -p build
    cd build
    cmake ../
    make

    echo "==== Usage ===="
    show_usage
}

# Show Usage
function show_usage(){
    echo "(1) Build"
    echo "bash ./01-build.sh"

    echo "(2) Run"
    echo "bash ./02-run.sh"

    echo "(3) Clean"
    echo "bash 03-clean.sh"
}

# Run
function run() {
    set -e     # stop script and exit the terminal when got any error
    
    mkdir -p build
    cd build
    cmake ../
    make

    set +e 
    ./test
}

# Clean
function clean(){
    local CleanScriptPath=`realpath .`

    set -e     # stop script and exit the terminal when got any error
    set -x 

    echo "Remove related libraries"
    rm -fr	"$CleanScriptPath"/build

    set +e
    set +x 
}