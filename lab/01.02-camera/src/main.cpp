#include <opencv2/opencv.hpp>
#include "test_util.h"
using namespace std;
using namespace cv;


void test_camera(Status &status);

int main() {
   Status status;

   test_camera(status);

   printf("status.bPass = %d \n", status.bPass);
   if(!status.bPass){
    printf("%s\n", status.msg.c_str());
    return -1;
   }

    printf("PASS");
    return 0;
}

// Test camera initial
// Arg: 
//   1. Result: 
//      bPass=true, if the test is pass the criteria
//       msg = the message
void test_camera(Status &status) {
    VideoCapture cap;

    //cap.open(0); // RGB camera
    cap.open(2); // IR camera
    if (!cap.isOpened()) {
        status.bPass = false;
        status.msg = "[Error] Cannot open camera";
        return;
    }
    
    Mat frame;
    Mat gray;
    
    bool ret=false;
    for(int i=0; i<3000; i++) {
        ret = cap.read(frame); // or cap >> frame;
        if (!ret) {
            status.bPass = false;
            status.msg = "[Error] Can't receive frame (stream end?). Exiting ...";
            return;
        }
        imshow("live", frame);
        if (waitKey(1) == 'q') {
            status.bPass = true;
            status.msg = "User input 'q' to pass. Exiting ...";
            return ;
        }
    }
    cap.release();

    status.bPass = true;
    status.msg = "Pass";
}