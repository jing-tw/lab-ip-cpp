#include <mylib/MyPictureCV.h> // super class

// // OpenGL
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>

// // OpenCV
// #include <opencv2/opencv.hpp>
// using namespace cv;

#include <mylib/mylibopencv.h>

// Mylib
#include <mylib/mylibopengl.h> 

void MyPictureCV::print() {
    #ifdef __MYDEBUG__
    printf("[__MYDEBUG__] class name = %s\n", "MyPictureCV");
    #endif
}

bool MyPictureCV::load(const char *path)
{
    this->path = path;
    // load image
    // Mat image = imread(path);
    this->image = imread(path);
    if (image.empty()) {
        std::cerr << "Could not load image!" << std::endl;
        return false;
    }
    this->height = image.rows;
    this->width = image.cols;

    // Mat to texture
    // this->texture = mat2Texture(image, true);
    cv::Mat image_flip = image.clone();
    this->texture = mat2Texture(image_flip, true);

    // initShader();
    return true;
}

// 應該要在同一塊畫布上,顯示完所有文字, 然後再一次產生texture
void MyPictureCV::drawText_SLOW(const char *text, Point org, Scalar color){
    cv::Mat image_flip = image.clone();
    test_drawText(image_flip, text, org, color);


    // update the texture
    glDeleteTextures(1, &this->texture); // Delete the texture
    this->texture = mat2Texture(image_flip, true);
}



// void MyPictureCV::updateTexture(Mat ){

// }

