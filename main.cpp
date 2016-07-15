#include <cstdio>
#include <iostream>
#include <Eigen/Dense>
#include <asio.hpp>

int main() {
  Eigen::Matrix3d m = Eigen::Matrix3d::Random();
  asio::io_service io;
  asio::basic_waitable_timer<std::chrono::system_clock> timer(io, std::chrono::system_clock::now() + std::chrono::seconds(5));
  timer.wait();
  std::cout << m << "\n";
  printf("Hello, World\n");
  return 0;
}
