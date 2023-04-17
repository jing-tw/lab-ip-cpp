#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


#include "image_util.h"

using namespace std;
using namespace cv;

bool impage_processing(const Mat &image) {
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    int height = gray.rows;
    int width = gray.cols;

    print_image_value(gray);
    cv::Size show_size = show_image(gray, "show_image");


    int* prj_v = new int[width];
    int prj_v_length = width;
    get_v_project(gray, prj_v, prj_v_length, "prj_v.csv");

    int* prj_h = new int[height];
    int prj_h_length = height;
    get_h_project(gray, prj_h, prj_h_length, "prj_h.csv");
    
    // int max_value = *std::max_element(std::begin(prj_v), std::end(prj_v));
    
    // int max_value = *std::max_element(prj_v, prj_v+width);
    // printf("max_value = %d \n", max_value);
    // cv::Mat out_image(max_value, width, CV_8UC1);
    // one_d_array_to_image(prj_v, width, out_image);
    // printf("show prj");
    // show_image2(out_image,"prj_v", -1, show_size.width);

    int* his_array = new int[256];
    get_histogram(gray, his_array, "his_array.csv");
    delete [] his_array;

    Mat bi_image(gray);
    bilevel_image(gray, 37, &bi_image);
    show_image(gray, "bi_image");
    return true;
}

int main() {
    std::string image_path = "../res/img/";
    std::string image = image_path + "right_eye.png";
    cv::Mat eyeRegion = cv::imread(image.c_str()); // cv::Mat eyeRegion = cv::imread("../right_eye.png");
    if (eyeRegion.empty()) {
        std::cerr << "Error loading the eye region image" << std::endl;
        return -1;
    }

    bool bOK = impage_processing(eyeRegion);

    return 0;
}

