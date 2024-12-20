// OpenCV
#include <opencv2/opencv.hpp>
using namespace cv;

bool drawText(Mat &image, const char *text, Point org, Scalar color, double fontScale, int thickness, int lineType);
bool test_drawText(Mat &image, const char *text, Point org, Scalar color);