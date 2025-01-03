// This code was copied from https://machinelearningspace.com/2d-object-tracking-using-kalman-filter/
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <mylib/Detector.hpp>

int ObjectDetection();

int main() {
    ObjectDetection();
}

int ObjectDetection(){
    cv::VideoCapture videocap("./data/randomball0.avi");

    // Check if camera opened successfully
    if(!videocap.isOpened()){
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    int debug_mode = 1;
    while (1) {
        cv::Mat frame;
        videocap >> frame;

        if (frame.empty()) {
            break;
        }

        auto centers = detect(frame, debug_mode);

        // If centers are detected, then we track them
        if (!centers.empty()) {	
            cv::circle(frame, centers[0], 10, cv::Scalar(0, 191, 255), 2);
            cv::Point pt7(int(centers[0].x + 35), int(centers[0].y + 30));
            cv::putText(frame, "Measured position", pt7, 0, 0.5, cv::Scalar(0, 191, 255), 2);
        }

        cv::imshow("image", frame);

        // Press ESC on keyboard to exit
        char c = (char)cv::waitKey(25);
        if (c == 27) {
            break;
        }
    }
    videocap.release();
    cv::destroyAllWindows();
    return 0;
}
