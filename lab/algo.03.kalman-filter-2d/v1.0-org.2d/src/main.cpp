/* Discrete Kalman filter implementation for object tracking
 * Reference: https://machinelearningspace.com/2d-object-tracking-using-kalman-filter/
 */

#include <cmath>
// #include <iostream>
#include <math.h>

#include <Eigen/Dense>

#include <iostream>
#include <random>
#include <vector>

#include "Detector.hpp"
//#include <Eigen/Dense>

// #include <matplot/matplot.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>


class KalmanFilter2D {
private:
    double dt = 0;                   // Time for one cycle
    Eigen::Vector2d u {0, 0};         // Control input
    Eigen::Vector4d x {0, 0, 0, 0};  // Initial State (position and velocity)

    // Standard deviations of acceleration(sigma_a) and measurement(sigma_z)
    double std_acc = 0, std_meas_x = 0, std_meas_y = 0;

    // State estimation matrix
    Eigen::Matrix4d A {
        {1, 0, dt,  0},
        {0, 1,  0, dt},
        {0, 0,  1,  0},
        {0, 0,  0,  1}
    };

    // Control input matrix
    Eigen::Matrix<double, 4, 2> B {
        {(dt * dt) / 2,             0},
        {            0, (dt * dt) / 2},
        {           dt,             0},
        {            0,            dt}
    };

    // State-to-measurement domain transformation matrix
    Eigen::Matrix<double, 2, 4> H {
        {1, 0, 0, 0},
        {0, 1, 0, 0}
    };
    
    // Process Noise Covariance
    double c1 = (pow(dt, 4) / 4), c2 = (pow(dt, 3) / 2), c3 = (dt * dt);
    double sig_a_2 = pow(std_acc, 2);
    Eigen::Matrix4d Q {
        {sig_a_2 * c1,            0, sig_a_2 * c2,            0},
        {           0, sig_a_2 * c1,            0, sig_a_2 * c2},
        {sig_a_2 * c2,            0, sig_a_2 * c3,            0},
        {           0, sig_a_2 * c2,            0, sig_a_2 * c3}
    };

    // Measurement Noise Covariance
    Eigen::Matrix2d R {
        {std_meas_x * std_meas_x,                       0},
        {                      0, std_meas_y * std_meas_y}
    };

    Eigen::Matrix4d P = Eigen::Matrix4d::Identity();  // Error Covariance

public:
    KalmanFilter2D(
        double dt_, double u_x_, double u_y_,
        double sigma_a, double sigma_z_x, double sigma_z_y
    ):dt(dt_), std_acc(sigma_a), std_meas_x(sigma_z_x), std_meas_y(sigma_z_y) {
        u[0] = u_x_;
        u[1] = u_y_;
    };

    // Time update equations:
    Eigen::Vector2d predict() {
        // Update time state:
        x = A * x + B * u;

        // Calculate error covariance:
        // P = (A * P * A') + Q
        P = A * P * A.transpose() + Q;
        
        return x.head(2);  // (Eigen::Vector2d)x(Eigen::seq(0, 2));
    }

    // Measurement update equations:
    Eigen::Vector2d update(cv::Point pt) {
        // Calculating Kalman gain (K):
        Eigen::Matrix2d S = (H * P * H.transpose()) + R;
        Eigen::Matrix<double, 4, 2> K = (P * H.transpose()) * S.inverse();

        Eigen::Vector2d z0 {pt.x, pt.y};
        x += K * (z0 - (H * x));
        x(0) = round(x(0));
        x(1) = round(x(1));

        Eigen::Matrix4d I = Eigen::Matrix4d::Identity();

        P = (I - (K * H)) * P;
        
        return x.head(2);  // (Eigen::Vector2d)x(Eigen::seq(0, 2));
    }

    // Getters:
    Eigen::Matrix4d get_A() {
        return A;
    }

    Eigen::Matrix<double, 4, 2> get_B() {
        return B;
    }

    Eigen::Matrix<double, 2, 4> get_H() {
        return H;
    }

    Eigen::Matrix4d get_Q() {
        return Q;
    }

    Eigen::Matrix2d get_R() {
        return R;
    }
};


/* Main program to test out the designed Discrete Kalman filter */






int KF2DImplementation(int debug_mode) {
    cv::VideoCapture videocap("./data/randomball0.avi");

    // Check if camera opened successfully
    if(!videocap.isOpened()){
        std::cout << "Error opening video stream or file" << std::endl;
        return -1;
    }

    double dt = 0.1;
    double u_x = 1, u_y = 1;
    double std_acc = 0.25;
    double std_meas_x = 0.1, std_meas_y = 0.1; 

    KalmanFilter2D kf = KalmanFilter2D(dt, u_x, u_y, std_acc, std_meas_x, std_meas_y);

    // int debug_mode = debug_mode;

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

            // Prediction
            auto prediction = kf.predict();
            auto x_p = prediction[0], y_p = prediction[1];
            cv::Point pt1(int(x_p - 15), int(y_p - 15)), pt2(int(x_p + 15), int(y_p + 15));
            cv::rectangle(frame, pt1, pt2, cv::Scalar(255, 0, 0), 2);

            // Correction
            auto correction = kf.update(centers[0]);
            auto x_c = correction[0], y_c = correction[1];
            cv::Point pt3(int(x_c - 16), int(y_c - 16)), pt4(int(x_c + 16), int(y_c + 16));
            cv::rectangle(frame, pt3, pt4, cv::Scalar(0, 0, 255), 2);

            cv::Point pt5(int(x_c + 15), int(y_c + 10)), pt6(int(x_p + 25), int(y_p + 20));
            cv::Point pt7(int(centers[0].x + 35), int(centers[0].y + 30));
            cv::putText(frame, "Estimated position", pt5, 0, 0.5, cv::Scalar(0, 0, 255), 2);
            cv::putText(frame, "Predicted position", pt6, 0, 0.5, cv::Scalar(255, 0, 0), 2);
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

int main() {
    KF2DImplementation(1);
}































// /**
// * Kalman filter implementation using Eigen. Based on the following
// * introductory paper:
// *
// *     http://www.cs.unc.edu/~welch/media/pdf/kalman_intro.pdf
// *     source: https://github.com/hmartiro/kalman-cpp/tree/master
// * @author: Hayk Martirosyan
// * @date: 2014.11.15
// */

// #include <iostream>
// #include <fstream>
// #include <Eigen/Dense>
// #include <mylib/kalman.h>


// int main(int argc, char* argv[]) {

//   int n = 3; // Number of states
//   int m = 1; // Number of measurements

//   double dt = 1.0/30; // Time step

//   Eigen::MatrixXd A(n, n); // System dynamics matrix
//   Eigen::MatrixXd C(m, n); // Output matrix
//   Eigen::MatrixXd Q(n, n); // Process noise covariance
//   Eigen::MatrixXd R(m, m); // Measurement noise covariance
//   Eigen::MatrixXd P(n, n); // Estimate error covariance

//   // Discrete LTI projectile motion, measuring position only
//   A << 1, dt, 0, 0, 1, dt, 0, 0, 1;
//   C << 1, 0, 0;

//   // Reasonable covariance matrices
//   Q << .05, .05, .0, .05, .05, .0, .0, .0, .0;
//   R << 5;
//   P << .1, .1, .1, .1, 10000, 10, .1, 10, 100;

//   std::cout << "A: \n" << A << std::endl;
//   std::cout << "C: \n" << C << std::endl;
//   std::cout << "Q: \n" << Q << std::endl;
//   std::cout << "R: \n" << R << std::endl;
//   std::cout << "P: \n" << P << std::endl;

//   // Construct the filter
//   KalmanFilter kf(dt,A, C, Q, R, P);

//   // List of noisy position measurements (y)
//   // std::vector<double> measurements = {
//   //     1.04202710058, 1.10726790452, 1.2913511148, 1.48485250951, 1.72825901034,
//   //     1.74216489744, 2.11672039768, 2.14529225112, 2.16029641405, 2.21269371128,
//   //     2.57709350237, 2.6682215744, 2.51641839428, 2.76034056782, 2.88131780617,
//   //     2.88373786518, 2.9448468727, 2.82866600131, 3.0006601946, 3.12920591669,
//   //     2.858361783, 2.83808170354, 2.68975330958, 2.66533185589, 2.81613499531,
//   //     2.81003612051, 2.88321849354, 2.69789264832, 2.4342229249, 2.23464791825,
//   //     2.30278776224, 2.02069770395, 1.94393985809, 1.82498398739, 1.52526230354,
//   //     1.86967808173, 1.18073207847, 1.10729605087, 0.916168349913, 0.678547664519,
//   //     0.562381751596, 0.355468474885, -0.155607486619, -0.287198661013, -0.602973173813
//   // };

//   // List of noisy position measurements (y)
//   std::vector<Eigen::Vector2d> measurements = {
//       {1.042, 0.978}, {1.107, 1.045}, {1.291, 1.234}, {1.485, 1.428}, {1.728, 1.675},
//       {1.742, 1.689}, {2.117, 2.065}, {2.145, 2.093}, {2.160, 2.108}, {2.213, 2.160},
//       {2.577, 2.525}, {2.668, 2.616}, {2.516, 2.464}, {2.760, 2.708}, {2.881, 2.829},
//       {2.884, 2.832}, {2.945, 2.893}, {2.829, 2.777}, {3.001, 2.949}, {3.129, 3.077},
//       {2.858, 2.806}, {2.838, 2.786}, {2.690, 2.638}, {2.665, 2.613}, {2.816, 2.764},
//       {2.810, 2.758}, {2.883, 2.831}, {2.698, 2.646}, {2.434, 2.382}, {2.235, 2.183},
//       {2.303, 2.251}, {2.021, 1.969}, {1.944, 1.892}, {1.825, 1.773}, {1.525, 1.473},
//       {1.870, 1.818}, {1.181, 1.129}, {1.107, 1.055}, {0.916, 0.864}, {0.679, 0.627},
//       {0.562, 0.510}, {0.355, 0.303}, {-0.156, -0.208}, {-0.287, -0.339}, {-0.603, -0.655}
//   };


//   // Best guess of initial states
//   Eigen::VectorXd x0(n);
//   double t = 0;
//   x0 << measurements[0], 0, -9.81;
//   kf.init(t, x0);

//   // // Feed measurements into filter, output estimated states
//   // // Value only
//   Eigen::VectorXd y(m);
//   std::cout << "t = " << t << ", " << "x_hat[0]: " << kf.state().transpose() << std::endl;
//   for(int i = 0; i < measurements.size(); i++) {
//     t += dt;
//     y << measurements[i];
//     kf.update(y);
//     std::cout << "t = " << t << ", " << "y[" << i << "] = " << y.transpose()
//         << ", x_hat[" << i << "] = " << kf.state().transpose() << std::endl;
//   }

//   // std::ofstream file("result.csv", std::ios::app); // Open file in append mode
//   // if (file.is_open()) {
//   //       Eigen::VectorXd y(m);
//   //       for(int i = 0; i < measurements.size(); i++) {

//   //         // kalman filter
//   //         t += dt;
//   //         y << measurements[i];
//   //         kf.update(y);
//   //         file << i << ", " << y.transpose() << ", " << kf.state().transpose()(0) << std::endl;
//   //         // end of kalman
//   //       }
//   //       file.close();
//   //       std::cout << "Number appended to file successfully." << std::endl;
//   //   } else {
//   //       std::cerr << "Unable to open file" << std::endl;
//   //   }
//   return 0;
// }

