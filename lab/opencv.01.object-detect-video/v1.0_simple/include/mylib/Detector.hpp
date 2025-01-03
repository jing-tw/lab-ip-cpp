/* This is a simple object detector made using classical image processing
 * algorithms through OpenCV package. It will detect single as well as multiple
 * objects
 */

#include <vector>

#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>


std::vector<cv::Point2f> detect(cv::Mat frame, int debug_mode) {
    // Converting from BGR to grayscale to filter out color information which we
    // do not need for edge detection
    cv::Mat gray;
    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

    if (debug_mode) {
        cv::imshow("gray", gray);
    }

    // Detecting edges using Canny Edge Detector
    // https://docs.opencv.org/3.4/da/d22/tutorial_py_canny.html
    cv::Mat edges;
    cv::Canny(gray, edges, 50, 190, 3);  // threshold1, threshold2, apertureSize
    if (debug_mode) {
        cv::imshow("edges", edges);
    }

    // Converting to black-and-white to obtain contours
    cv::Mat threshold;
    cv::threshold(edges, threshold, 254, 255, cv::THRESH_BINARY);
    if (debug_mode) {
        cv::imshow("threshold", threshold);
    }

    // Finding contours for shape analysis and object detection
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(threshold, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Setting accepted minimum and maximum radius for minimum enclosing circle
    // which encloses the detected object
    int min_radius = 3, max_radius = 30;

    std::vector<cv::Point2f> centers = {};
    cv::Point2f center;
    float radius;
    for (auto contour:contours) {
        cv::minEnclosingCircle(contour, center, radius);
        radius = int(radius);  // To simplify thresholding

        if (radius > min_radius && radius < max_radius) {
            centers.push_back(center);
        }
    }

    // cv::imshow("contours", threshold);
    return centers;
}