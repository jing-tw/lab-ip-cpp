#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

class Status{
    public:
        bool bRet;
        std::string Msg;

    public:
        Status(bool bRet, std::string Msg){
            this->bRet = bRet;
            this->Msg = Msg;
        }
};

cv::Size  show_image(const cv::Mat image, const char* title);
cv::Size  show_image2(const cv::Mat image, const char* title, int def_height, int def_width);
bool get_histogram(const cv::Mat &image, int* his_array, const char* out_csv_filename);
bool save_csv_int_array(int* arr, int length, const char* out_csv_filename);
void print_image_value(const cv::Mat image);
bool bilevel_image(const cv::Mat image, int threshold, cv::Mat *newImage);
bool get_v_project(const cv::Mat &image, int* prj, int prj_length, const char* out_csv_filename);
bool get_h_project(const cv::Mat &image, int* prj, int prj_length, const char* out_csv_filename);
bool one_d_array_to_image(int* array, int length, cv::Mat &out_image);
bool get_h_sym_1d(const cv::Mat &image, int y, int* ret_arr_sym);
bool get_h_sym_2d(const cv::Mat &image, const char* out_csv_filename);
Status print_1d_array(std::string title, int* arr, int length);

