// OpenGL
#include <opencv2/opencv.hpp>
// #include <opencv2/imgproc/imgproc.hpp>
// #include <opencv2/highgui/highgui.hpp>

// Base class
#include <mylib/MyPictureCV.h>

using namespace cv;

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

GLuint MyPictureCV::mat2Texture(Mat image) {
    // Convert image to RGB format for OpenGL
    cvtColor(image, image, COLOR_BGR2RGB);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.cols, image.rows, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image.data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}
