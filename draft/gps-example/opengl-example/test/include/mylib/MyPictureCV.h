
// Bass class
#include <mylib/MyPicture.h>

// OpenCV
#include <opencv2/opencv.hpp>
using namespace cv;

// MyPictureCV: CV version 
// Usage:
/*
    MyPicture *myPicture = new MyPictureCV();
    myPicture->load("cs-black-000.png");
    while(1){
        myPicture->display(0.0f, 0.0f, offset, view, projection);
    }
*/
class MyPictureCV: public MyPicture{
    private:
        Mat image;

    public:
        MyPictureCV(float d=0.5f, float z=0.0f);
        bool load(const char* path);
        void print();
        void drawText_SLOW(const char *text, Point org, Scalar color);
};