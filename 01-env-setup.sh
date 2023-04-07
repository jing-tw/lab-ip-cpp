#!/bin/bash
# Installation script 

function main() {
    local INSTALL_SCRIPT_PATH=`realpath ./`
    local PROJECT_PATH="$INSTALL_SCRIPT_PATH"/project

    #set -e     # stop script and exit the terminal when got any error
    msg_wait_sec=5

    util_message "==== Step 1: Install the tool chain ====", msg_wait_sec
    sudo apt-get update
    sudo apt-get install -y build-essential git
    sudo apt-get install -y pkg-config
    sudo apt-get install -y libcanberra-gtk-module libcanberra-gtk3-module  # for canberra-gtk-module
    sudo apt install -y libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav  # for gstreamer1.0
    sudo apt-get install -y libgstrtspserver-1.0-dev gstreamer1.0-rtsp  # for gstreamer-rtsp-server-1.0
    sudo apt-get install -y mosquitto-dev libmosquitto-dev libmosquitto1 libmosquittopp1 mosquitto-clients  # for mosquitto

    util_message "==== Step 2: Build the FFMPEG (v4.4.3) ====" msg_wait_sec
    install_ffmepg

    util_message "==== Step 3: Build the OpenCV (v4.1.0) ====" msg_wait_sec
    install_opencv
    export OpenCV_DIR="$INSTALL_SCRIPT_PATH"/opencv_build
    export LD_LIBRARY_PATH="$OpenCV_DIR"/lib/ # for ncnn version
    
    util_message "==== Step 4: Build the ncnn ===="
    install_ncnn "$PROJECT_PATH"

    util_message "==== Step 5: Build the project ===="
    build_project

    echo "Complete!"
    show_usage
}

function install_ffmepg() {
    sudo apt-get install -y yasm libx264-dev x264 libv4l-dev
    sudo apt-get install -y libunistring-dev libaom-dev
    # sudo apt-get install -y libdavid-dev  # Unable to locate package libdavid-dev

    git clone --depth 1 --branch n4.4.3 https://github.com/FFmpeg/FFmpeg.git

    cd FFmpeg
    ./configure --extra-cflags="-fPIC" --enable-nonfree --enable-gpl --enable-libx264 --enable-indev=v4l2 --enable-ffplay --enable-pic --enable-shared
    make -j`nproc`
    sudo make install
    cd ..
}

function install_opencv() {
    sudo apt-get install  -y cmake libgtk2.0-dev libavcodec-dev libavformat-dev libswscale-dev
    git clone --depth 1 --branch 4.1.0 https://github.com/opencv/opencv.git  # Apr 8, 2019, 4.1.0
    git clone  --depth 1 --branch 4.1.0  https://github.com/opencv/opencv_contrib.git   # get the extra module

    mkdir opencv_build
    cd opencv_build
    cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules ../opencv -D CMAKE_BUILD_TYPE=Debug -D CMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_SHARED_LINKER_FLAGS=-Wl,-Bsymbolic
    make -j`nproc`
    cd ..
}

function install_ncnn() {
    local PROJECT_PATH=$1
    # build
    git clone https://github.com/Tencent/ncnn.git
    cd ncnn
    git submodule update --init
    mkdir build 
    cd build

    # BSP
    # . /opt/bsp-5.4.70-2.3.3/environment-setup-aarch64-poky-linux # You can refer to it from doc/BSP.md
    cmake ..
    make -j`nproc`

    # install
    make install
    cp -fr install/include/* "$PROJECT_PATH"/include/nn/
    cp -fr install/lib/libncnn.a "$PROJECT_PATH"/lib
    
    cd .. # leave build
    cd .. # leave ncnn
}

function build_project(){
    mkdir build
    cd build

    cmake ../src/
    make -j$(nproc)

    cd .. # leave build
}

function show_usage(){
    echo "== Build Project =="
    echo "cd build"
    echo "cmake ../src/"
    echo "make -j$(nproc)"

    echo "== Run Project =="
    echo "cd build"
    echo "./test"
}


# util_message Show message and wait second fo nootification
# $1: string, a message for show
# $2: number, the second for wait 
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

main
