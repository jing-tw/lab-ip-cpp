// OpenCV
#include <opencv2/opencv.hpp>

// Bass class
#include <mylib/MyPicture.h>

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
    public:
        bool load(const char* path);
        void print();
        
    private:
        // GLuint loadTexture_OpenCV(const char* path, int& width, int& height);
        GLuint mat2Texture(cv::Mat image);
};