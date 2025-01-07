#include <mylib/mylibopencv.h>

bool drawText(Mat &image, const char *text, Point org, Scalar color, double fontScale, int thickness, int lineType)
{
    int fontFace = FONT_HERSHEY_SIMPLEX;
    putText(image, text, org, fontFace, fontScale, color, thickness, lineType);
    return true;
}


bool drawText(Mat &image, const char *text, Point org, Scalar color){
    // Define the text to be displayed
    // std::string text = "Hello, OpenCV!";
    
    // Set the position for the text
    // Point position(image.cols/2, image.rows/2); // x=50, y=50

    // Set font type and scale
    int fontFace = FONT_HERSHEY_SIMPLEX;
    double fontScale = 1;
    
    // Set color (BGR format)
    // Scalar color(0, 0, 255); // White color

    // Set thickness
    int thickness = 2;

    // Put text on the image
    // putText(image, text, position, fontFace, fontScale, color, thickness);
    putText(image, text, org, fontFace, fontScale, color, thickness);

    return true;
}