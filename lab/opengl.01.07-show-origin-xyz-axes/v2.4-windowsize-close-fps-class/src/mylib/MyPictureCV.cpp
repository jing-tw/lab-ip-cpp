#include <mylib/MyPictureCV.h> // super class

// OpenGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// OpenCV
#include <opencv2/opencv.hpp>
using namespace cv;

// Mylib
#include <mylib/mylib.h> 

void MyPictureCV::print() {
    #ifdef __MYDEBUG__
    printf("[__MYDEBUG__] class name = %s\n", "MyPictureCV");
    #endif
}

bool MyPictureCV::load(const char *path)
{
    this->path = path;
    // load image
    Mat image = imread(path);
    if (image.empty()) {
        std::cerr << "Could not load image!" << std::endl;
        return false;
    }
    this->height = image.rows;
    this->width = image.cols;

    // Mat to texture
    this->texture = mat2Texture(image);

    initShader();
    return true;
}


