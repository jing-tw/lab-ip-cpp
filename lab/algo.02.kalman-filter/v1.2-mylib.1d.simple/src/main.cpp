
/**
* Kalman filter implementation using Eigen. Based on the following
* introductory paper:
*
*     http://www.cs.unc.edu/~welch/media/pdf/kalman_intro.pdf
*     source: https://github.com/hmartiro/kalman-cpp/tree/master
* @author: Hayk Martirosyan
* @date: 2014.11.15
*/

#include <iostream>
#include <fstream>
#include <Eigen/Dense>

#include <mylib/kalman.h>

// #pragma once

// class KalmanFilter {

// public:

//   /**
//   * Create a Kalman filter with the specified matrices.
//   *   A - System dynamics matrix
//   *   C - Output matrix
//   *   Q - Process noise covariance
//   *   R - Measurement noise covariance
//   *   P - Estimate error covariance
//   */
//   KalmanFilter(
//       double dt,
//       const Eigen::MatrixXd& A,
//       const Eigen::MatrixXd& C,
//       const Eigen::MatrixXd& Q,
//       const Eigen::MatrixXd& R,
//       const Eigen::MatrixXd& P
//   );

//   /**
//   * Create a blank estimator.
//   */
//   KalmanFilter();

//   /**
//   * Initialize the filter with initial states as zero.
//   */
//   void init();

//   /**
//   * Initialize the filter with a guess for initial states.
//   */
//   void init(double t0, const Eigen::VectorXd& x0);

//   /**
//   * Update the estimated state based on measured values. The
//   * time step is assumed to remain constant.
//   */
//   void update(const Eigen::VectorXd& y);

//   /**
//   * Update the estimated state based on measured values,
//   * using the given time step and dynamics matrix.
//   */
//   void update(const Eigen::VectorXd& y, double dt, const Eigen::MatrixXd A);

//   /**
//   * Return the current state and time.
//   */
//   Eigen::VectorXd state() { return x_hat; };
//   double time() { return t; };

// private:

//   // Matrices for computation
//   Eigen::MatrixXd A, C, Q, R, P, K, P0;

//   // System dimensions
//   int m, n;

//   // Initial and current time
//   double t0, t;

//   // Discrete time step
//   double dt;

//   // Is the filter initialized?
//   bool initialized;

//   // n-size identity
//   Eigen::MatrixXd I;

//   // Estimated states
//   Eigen::VectorXd x_hat, x_hat_new;
// };



// KalmanFilter::KalmanFilter(
//     double dt,
//     const Eigen::MatrixXd& A,
//     const Eigen::MatrixXd& C,
//     const Eigen::MatrixXd& Q,
//     const Eigen::MatrixXd& R,
//     const Eigen::MatrixXd& P)
//   : A(A), C(C), Q(Q), R(R), P0(P),
//     m(C.rows()), n(A.rows()), dt(dt), initialized(false),
//     I(n, n), x_hat(n), x_hat_new(n)
// {
//   I.setIdentity();
// }

// KalmanFilter::KalmanFilter() {}

// void KalmanFilter::init(double t0, const Eigen::VectorXd& x0) {
//   x_hat = x0;
//   P = P0;
//   this->t0 = t0;
//   t = t0;
//   initialized = true;
// }

// void KalmanFilter::init() {
//   x_hat.setZero();
//   P = P0;
//   t0 = 0;
//   t = t0;
//   initialized = true;
// }

// void KalmanFilter::update(const Eigen::VectorXd& y) {

//   if(!initialized)
//     throw std::runtime_error("Filter is not initialized!");

//   x_hat_new = A * x_hat;
//   P = A*P*A.transpose() + Q;
//   K = P*C.transpose()*(C*P*C.transpose() + R).inverse();
//   x_hat_new += K * (y - C*x_hat_new);
//   P = (I - K*C)*P;
//   x_hat = x_hat_new;

//   t += dt;
// }

// void KalmanFilter::update(const Eigen::VectorXd& y, double dt, const Eigen::MatrixXd A) {
//   this->A = A;
//   this->dt = dt;
//   update(y);
// }


// /**
//  * Test for the KalmanFilter class with 1D projectile motion.
//  *
//  * @author: Hayk Martirosyan
//  * @date: 2014.11.15
//  */

// #include <iostream>
// #include <vector>
// #include <Eigen/Dense>

// #include <mylib/kalman.h>


int main(int argc, char* argv[]) {

  int n = 3; // Number of states
  int m = 1; // Number of measurements

  double dt = 1.0/30; // Time step

  Eigen::MatrixXd A(n, n); // System dynamics matrix
  Eigen::MatrixXd C(m, n); // Output matrix
  Eigen::MatrixXd Q(n, n); // Process noise covariance
  Eigen::MatrixXd R(m, m); // Measurement noise covariance
  Eigen::MatrixXd P(n, n); // Estimate error covariance

  // Discrete LTI projectile motion, measuring position only
  A << 1, dt, 0, 0, 1, dt, 0, 0, 1;
  C << 1, 0, 0;

  // Reasonable covariance matrices
  Q << .05, .05, .0, .05, .05, .0, .0, .0, .0;
  R << 5;
  P << .1, .1, .1, .1, 10000, 10, .1, 10, 100;

  std::cout << "A: \n" << A << std::endl;
  std::cout << "C: \n" << C << std::endl;
  std::cout << "Q: \n" << Q << std::endl;
  std::cout << "R: \n" << R << std::endl;
  std::cout << "P: \n" << P << std::endl;

  // Construct the filter
  KalmanFilter kf(dt,A, C, Q, R, P);

  // List of noisy position measurements (y)
  std::vector<double> measurements = {
      1.04202710058, 1.10726790452, 1.2913511148, 1.48485250951, 1.72825901034,
      1.74216489744, 2.11672039768, 2.14529225112, 2.16029641405, 2.21269371128,
      2.57709350237, 2.6682215744, 2.51641839428, 2.76034056782, 2.88131780617,
      2.88373786518, 2.9448468727, 2.82866600131, 3.0006601946, 3.12920591669,
      2.858361783, 2.83808170354, 2.68975330958, 2.66533185589, 2.81613499531,
      2.81003612051, 2.88321849354, 2.69789264832, 2.4342229249, 2.23464791825,
      2.30278776224, 2.02069770395, 1.94393985809, 1.82498398739, 1.52526230354,
      1.86967808173, 1.18073207847, 1.10729605087, 0.916168349913, 0.678547664519,
      0.562381751596, 0.355468474885, -0.155607486619, -0.287198661013, -0.602973173813
  };

  // Best guess of initial states
  Eigen::VectorXd x0(n);
  double t = 0;
  x0 << measurements[0], 0, -9.81;
  kf.init(t, x0);

  // // Feed measurements into filter, output estimated states
  // // Value only
  // Eigen::VectorXd y(m);
  // std::cout << "t = " << t << ", " << "x_hat[0]: " << kf.state().transpose() << std::endl;
  // for(int i = 0; i < measurements.size(); i++) {
  //   t += dt;
  //   y << measurements[i];
  //   kf.update(y);
  //   std::cout << "t = " << t << ", " << "y[" << i << "] = " << y.transpose()
  //       << ", x_hat[" << i << "] = " << kf.state().transpose() << std::endl;
  // }

  std::ofstream file("result.csv", std::ios::app); // Open file in append mode
  if (file.is_open()) {
        Eigen::VectorXd y(m);
        for(int i = 0; i < measurements.size(); i++) {

          // kalman filter
          t += dt;
          y << measurements[i];
          kf.update(y);
          file << i << ", " << y.transpose() << ", " << kf.state().transpose()(0) << std::endl;
          // end of kalman
        }
        file.close();
        std::cout << "Number appended to file successfully." << std::endl;
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }
  return 0;
}

