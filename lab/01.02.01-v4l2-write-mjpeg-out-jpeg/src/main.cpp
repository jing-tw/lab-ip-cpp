#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>
#include <sys/mman.h>
#include <opencv2/opencv.hpp>


#define DEVICE_PATH "/dev/video0"
#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480

int main() {
    int fd = open(DEVICE_PATH, O_RDWR);

    if (fd == -1) {
        perror("Failed to open device");
        return 1;
    }

    struct v4l2_capability caps;
    if (ioctl(fd, VIDIOC_QUERYCAP, &caps) == -1) {
        perror("Failed to query capabilities");
        close(fd);
        return 1;
    }

    if (!(caps.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
        std::cerr << "Device does not support video capture" << std::endl;
        close(fd);
        return 1;
    }

    struct v4l2_format format;
    format.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    format.fmt.pix.width = IMAGE_WIDTH;
    format.fmt.pix.height = IMAGE_HEIGHT;
    format.fmt.pix.pixelformat =  V4L2_PIX_FMT_MJPEG; // V4L2_PIX_FMT_YUYV; // V4L2_PIX_FMT_RGB24; //V4L2_PIX_FMT_MJPEG; // MJPEG pixel format
    format.fmt.pix.field = V4L2_FIELD_NONE;

    if (ioctl(fd, VIDIOC_S_FMT, &format) == -1) {
        perror("Failed to set format");
        close(fd);
        return 1;
    }

    struct v4l2_requestbuffers req;
    req.count = 1;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (ioctl(fd, VIDIOC_REQBUFS, &req) == -1) {
        perror("Failed to request buffer");
        close(fd);
        return 1;
    }

    struct v4l2_buffer buffer;
    memset(&buffer, 0, sizeof(buffer));
    buffer.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buffer.memory = V4L2_MEMORY_MMAP;
    buffer.index = 0;

    if (ioctl(fd, VIDIOC_QUERYBUF, &buffer) == -1) {
        perror("Failed to query buffer");
        close(fd);
        return 1;
    }

    void *buffer_start = mmap(nullptr, buffer.length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, buffer.m.offset);
    if (buffer_start == MAP_FAILED) {
        perror("Failed to map buffer");
        close(fd);
        return 1;
    }

    if (ioctl(fd, VIDIOC_QBUF, &buffer) == -1) {
        perror("Failed to queue buffer");
        close(fd);
        return 1;
    }

    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (ioctl(fd, VIDIOC_STREAMON, &type) == -1) {
        perror("Failed to start streaming");
        close(fd);
        return 1;
    }

    if (ioctl(fd, VIDIOC_DQBUF, &buffer) == -1) {
        perror("Failed to dequeue buffer");
        close(fd);
        return 1;
    }

    // write to the test.jpg
    FILE* fout;
    fout = fopen("test.jpg", "wb");
    if (!fout) {
        perror("Cannot open image");
        exit(EXIT_FAILURE);
        }
    printf("(buffer).bytesused 2= %d\n", (buffer).bytesused);
    fwrite(buffer_start, (buffer).bytesused, 1, fout); 
    fclose(fout);

    // open to test
    cv::Mat image2 = cv::imread("./test.jpg");
    if (image2.empty() == true) {
        std::cout << "image2 empty"<< std::endl;
        return 0;
    }   
        
    cv::imshow("opencv_logo", image2);
    cv::waitKey(0);

    
    if (ioctl(fd, VIDIOC_STREAMOFF, &type) == -1) {
        perror("Failed to stop streaming");
        close(fd);
        return 1;
    }

    munmap(buffer_start, buffer.length);
    close(fd);

    return 0;
}
