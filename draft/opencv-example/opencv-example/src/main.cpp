// This code was copied from https://machinelearningspace.com/2d-object-tracking-using-kalman-filter/
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <mylib/Detector.hpp>
#include <ByteTrack/BYTETracker.h>
#include <ByteTrack/Rect.h>

// Reference
// https://github.com/Vertical-Beach/ByteTrack-cpp/blob/main/include/ByteTrack/BYTETracker.h

int ObjectDetection();

int main()
{
    ObjectDetection();
}

int ObjectDetection()
{
    cv::VideoCapture videocap("./data/randomball0.avi");

    // Check if camera opened successfully
    if (!videocap.isOpened())
    {
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    // init Byte Track
    float track_thresh = 0.5;
    int track_buffer = 30;
    float high_thresh = 0.85;
    float match_thresh = 0.8;
    int frame_rate = 30;

     byte_track::BYTETracker tracker(track_buffer, track_thresh, high_thresh, match_thresh);
    // end

    int debug_mode = 1;

    int frame_id = 0;
    while (1)
    {
        cv::Mat frame;
        videocap >> frame;

        if (frame.empty())
        {
            break;
        }

        auto centers = detect(frame, debug_mode);

        // If centers are detected, then we track them
        // if (!centers.empty()) {
        int classID = 1;
        for (const auto &center : centers)
        {
            std::vector<byte_track::Object> objects;

            // Show measured position
            cv::circle(frame, center, 10, cv::Scalar(0, 191, 255), 2);
            cv::Point pt7(int(center.x + 35), int(center.y + 30));
            cv::putText(frame, "Measured position", pt7, 0, 0.5, cv::Scalar(0, 191, 255), 2);

            // Update the tracker
            int x = center.x, y = center.y;
            int height = 16;
            int width = 16;
            float score = 0.9f;

            byte_track::Rect<float> rect(x, y, width, height);
            byte_track::Object obj(rect, classID, score);

            std::cout << "push back" << std::endl;            
            objects.push_back(obj);
            // using STrackPtr = std::shared_ptr<byte_track::STrack>;
            // std::vector<STrackPtr> output_stracks = tracker.update(objects);
            std::cout << "objects.size() = "<< objects.size() << std::endl;
            auto output_stracks = tracker.update(objects);

            frame_id++;

            // // Draw tracking results on the frame
            // for (const auto& track : tracker.tracks) {
            //     cv::rectangle(frame, track.bbox, cv::Scalar(0, 255, 0), 2);
            //     cv::putText(frame, std::to_string(track.id), track.bbox.tl(),
            //                 cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 0, 0), 2);
            // }

            // Process the output tracks (e.g., display, save, etc.)
            // for (const auto& track : output_stracks) {
            //     std::cout << "Track ID: " << track.track_id << " Position: (" << track.tlwh[0] << ", " << track.tlwh[1] << ")" << std::endl;
            // }

            // for (auto it = output_stracks.begin(); it != output_stracks.end(); ++it)
            // {
            //     STrackPtr track = *it;
            //     auto rect = track->getRect();
            //     cv::Rect cvRect(rect.x(), rect.y(), rect.width(), rect.height());
            //     cv::rectangle(frame, cvRect, cv::Scalar(0, 255, 0), 2);
            //     std::cout << "Track ID: " << track->getTrackId() << " Position: (" << track->getRect().x() << ", " <<  track->getRect().y() << ")" << std::endl;
            // }

            for (const auto& track : output_stracks) {
                auto rect = track->getRect();
                cv::Rect cvRect(rect.x(), rect.y(), rect.width(), rect.height());
                cv::rectangle(frame, cvRect, cv::Scalar(0, 255, 0), 2);
                std::cout << "Track ID: " << track->getTrackId() << " Position: (" << track->getRect().x() << ", " <<  track->getRect().y() << ")" << std::endl;
            }

            std::cout << frame_id << " output_stracks = " << output_stracks.size() << std::endl;
        }

        cv::imshow("image", frame);

        // Press ESC on keyboard to exit
        char c = (char)cv::waitKey(25);
        if (c == 27)
        {
            break;
        }
    }
    videocap.release();
    cv::destroyAllWindows();
    return 0;
}
