#include <opencv2/objdetect.hpp>
#include <opencv2/opencv.hpp>
#include "test_util.h"
using namespace std;
using namespace cv;


void test_qrcode(Status &status);

int main() {
   Status status;

   test_qrcode(status);

   printf("status.bPass = %d \n", status.bPass);
   if(!status.bPass){
    printf("%s\n", status.msg.c_str());
    return -1;
   }

    printf("PASS");
    return 0;
}

void display(Mat &im, Mat &bbox)
{
  int n = bbox.rows;
  for(int i = 0 ; i < n ; i++)
  {
    line(im, Point2i(bbox.at<float>(i,0),bbox.at<float>(i,1)), Point2i(bbox.at<float>((i+1) % n,0), bbox.at<float>((i+1) % n,1)), Scalar(255,0,0), 3);
  }
  imshow("Result", im);
}

void test_qrcode(Status &status) {
    
    Mat frame;
    Mat gray;

    // initial qr code decoder
    cv::QRCodeDetector qrDecoder;
    char* strName = "../res/qrcode-30-degree.png"; // "../res/qrcode-multi.png";  // "../res/qrcode-76.png"
    cv::Mat image2 = cv::imread(strName);
    if (image2.empty() == true) {
        std::cout << "image2 empty"<< std::endl;
        return ;
    }   
        
    cv::imshow(strName, image2);
    // cv::waitKey(0);


    // QR code processing
    Mat inputImage = image2;
    Mat bbox, rectifiedImage;
 
    std::string data = qrDecoder.detectAndDecode(inputImage, bbox, rectifiedImage);
    if(data.length()>0)
    {
        cout << "Decoded Data : " << data << endl;
        
        display(inputImage, bbox);
        rectifiedImage.convertTo(rectifiedImage, CV_8UC3);
        imshow("Rectified QRCode", rectifiedImage);
        
        waitKey(0);
    }
    else
    {
        cout << "QR Code not detected" << endl;
    }
    
    cv::waitKey(0);
    

    status.bPass = true;
    status.msg = "Pass";
}
