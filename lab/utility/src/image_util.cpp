#include "image_util.h"
//#include "test_util.h"

using namespace std;

cv::Size  show_image(const cv::Mat image, const char* title){
    return show_image2(image, title, 100, -1);
}

/*
Reference
1. https://stackoverflow.com/questions/35180764/opencv-python-image-too-big-to-display

*/
cv::Size show_image2(const cv::Mat image, const char* title, int def_height, int def_width){
    int height = image.rows;
    int width = image.cols;

    cv::Size newSize;

    if(def_height != -1 && def_width != -1){
        newSize = cv::Size(height, width);
        cv::Mat new_image;
        cv::resize(image, new_image, newSize, cv::INTER_LINEAR);
        cv::imshow(title, new_image);
        cv::waitKey();
        return cv::Size(new_image.cols, new_image.rows);
    }

    if (def_height != -1){
        float r = def_height / float(height);
        newSize = cv::Size(int(width * r), def_height);
    }
    
    if (def_width != -1){
        float r = def_width / float(width);
        newSize = cv::Size(def_width, int(height * r));
    }

    cv::Mat new_image;
    cv::resize(image, new_image, newSize, cv::INTER_LINEAR);
    cv::imshow(title, new_image);
    cv::waitKey();

    return cv::Size(new_image.cols, new_image.rows);
}

void print_image_value(const cv::Mat image){
    printf("== print_image_value ==\n");
    int height = image.rows;
    int width = image.cols;

    for(int y=0; y<height; y++){
        for(int x=0; x<width; x++){
            printf("y=%d, x=%d, value = %d\n", y, x, image.at<uchar>(y,x));
        }
    }
}

bool get_histogram(const cv::Mat &image, int* his_array, const char* out_csv_filename){
    if (his_array == NULL){
        printf("Error:: his_array == NULL");
        return false;
    }

    memset((int*) his_array, 0, 256);

    int height = image.rows;
    int width = image.cols;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char gray = image.at<uchar>(y,x);
            if (gray > 255){
                printf("Error:: gray > 255\n");
                printf("y=%d, x=%d, value = %d\n", y, x, image.at<uchar>(y,x));
                return false;
            }
            if(gray < 0){
                printf("Error:: gray < 0 \n");
                printf("y=%d, x=%d, value = %d\n", y, x, image.at<uchar>(y,x));
                return false;
            }

            his_array[(int)gray] ++;
        }
    }

    // save to file
    if(out_csv_filename != NULL){
        save_csv_int_array(his_array, 256, out_csv_filename);
    }
   
    return true;
}

bool save_csv_int_array(int* arr, int length, const char* out_csv_filename){
    ofstream out_file;
    out_file.open(string(out_csv_filename), std::ios_base::trunc);
    for(int i = 0; i< length; i++){
       out_file << arr[i] << endl;
    }
    out_file.close();
    printf("CSV File: %s\n", out_csv_filename);

    return true;
}

bool bilevel_image(const cv::Mat image, int threshold, cv::Mat *newImage){
    if (newImage == NULL){
        return false;
    }

    int height = image.rows;
    int width = image.cols;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            char gray = image.at<uchar>(y,x);
            
            if ((int)gray > threshold)
                newImage->at<uchar>(y,x) = 255;
            else
                newImage->at<uchar>(y,x) = 0;
        }
    }

    return true;
}

void print_1d_array(const char* title, int* arr, int length, Status &status){
    printf("%s\n", title);
    for(int i = 0; i< length; i++){
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    status.update(true, "ok");
}

bool get_h_sym_2d(const cv::Mat &image, const char* out_csv_filename){
    int height = image.rows;
    int width = image.cols;
    bool bOk = false;

    int* ret_arr_sym = new int[width];
    memset((int*) ret_arr_sym, 0, width);

    for(int y = 0; y < height; y ++)
        get_h_sym_1d(image, y, ret_arr_sym);
    delete[] ret_arr_sym;

    return true;
}

// calcuate the sym value
/* Usage:
   int[] ret_arr_sym = new int[width];
   get_h_sym_1d(image, y, ret_arr_sym)
   delete[] ret_arr_sym;
*/
bool get_h_sym_1d(const cv::Mat &image, int y, int* ret_arr_sym){
    int height = image.rows;
    int width = image.cols;

    if (width < 3){
        printf("Warning: the image width < 3\n");
        ret_arr_sym[0] = 65535;
        return false;
    }


    for(int x = 0; x < width; x++){
        if (x == 0 || x == width -1){
            ret_arr_sym[x] = 65535;
            continue;
        }

        int dleft = abs(x);
        int dright = abs(width - x -1);
        int dmin = (dleft < dright) ? dleft: dright;

        for(int d=1; d<dmin; d++){
            int left = (unsigned int) image.at<uchar>(y, x-d);
            int right = (unsigned int) image.at<uchar>(y, x+d); 
            ret_arr_sym[x] += abs(left - right);  // if left and right are simuilar, the value will be small;
        }
    }

    return true;
}

/*
Vertical Projection
Usage:
    int* prj = new int[width];
    get_v_project(image, prj);
    delete[] prj;
*/
bool get_v_project(const cv::Mat &image, int* prj, int prj_length, const char* out_csv_filename){
    int height = image.rows;
    int width = image.cols;
    bool bOk = false;

    if (prj == NULL){
        printf("Error: prj == NULL\n");
        return false;
    }

    for(int x=0; x<width; x++){
        prj[x] = 0;
        for(int y=0; y<height; y++){
            prj[x] += (unsigned int) image.at<uchar>(y, x); 
            
        }
        printf("x = %d, prj[x] = %d\n", x, prj[x]);
    }

    // save to file
    if(out_csv_filename != NULL){
        bOk = save_csv_int_array(prj, prj_length, out_csv_filename);
    }

    return bOk;
}

/*
Vertical Projection
Usage:
    int* prj = new int[height];
    get_h_project(image, height, prj);
    delete[] prj;
*/
bool get_h_project(const cv::Mat &image, int* prj, int prj_length, const char* out_csv_filename){
    int height = image.rows;
    int width = image.cols;
    bool bOk = false;

    if (prj == NULL){
        printf("Error: prj == NULL\n");
        return false;
    }

    for(int y=0; y<height; y++){
        prj[y] = 0;
        for(int x=0; x<width; x++){
            prj[y] += (unsigned int) image.at<uchar>(y, x); 
            
        }
        printf("y = %d, prj[y] = %d\n", y, prj[y]);
    }

    // save to file
    if(out_csv_filename != NULL){
        bOk = save_csv_int_array(prj, prj_length, out_csv_filename);
    }

    return bOk;
}


/*
Usage:
    int* array_1d = new int[length];
    ...
    int max_value = *std::max_element(std::begin(array_1d), std::end(array_1d));
    cv::Mat out_image(max_value, length);
    one_d_array_to_image(array_1d, length, out_image)
*/

bool one_d_array_to_image(int* array, int length, cv::Mat &out_image){
    if (array == NULL){
        printf("Error: array == NULL\n");
        return false;
    }

    int height = out_image.rows;
    int width = out_image.cols;
    // out_image = 0;

    for(int x = 0; x<length; x++){
        unsigned char value = array[x];
        printf("x = %d, value = %d \n", x, value);

        if (value > height){
            printf("Error: value > width \n");
            printf(" value = %d, width = %d \n", value, width);
            return false;
        }
        for(int y=0; y<(unsigned int)value; y++){
            out_image.at<uchar>(y, x) = 0xff;
        }
    }

    return true;
}