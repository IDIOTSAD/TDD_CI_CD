//
// Created by changh95 on 5/26/22.
//

#ifndef SVSLAM_MATRIX_MUL_HPP
#define SVSLAM_MATRIX_MUL_HPP

#define USING_EASY_PROFILER
#include "easy/profiler.h"
#include "spdlog/spdlog.h"
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <thread>
#include <mutex>
#include <sstream>
#include <random>
#include <opencv2/opencv.hpp>

class matrix_mul {
private:
  alignas(64) std::vector<float> a;
  alignas(64) std::vector<float> b;
  alignas(64) std::vector<float> c;
  alignas(64) std::vector<float> t;
  int m;
  int k;
  int n;
public:
  matrix_mul() {
    this->genmat(200, 200, a);
    this->genmat(200, 200, b);
    this->genmat(200, 200, c);
    this->genmat(200, 200, t);
    m = 200;
    k = 200;
    n = 200;
  }
  matrix_mul(int value) {
    this->genmat(value, value, a);
    this->genmat(value, value, b);
    this->genmat(value, value, c);
    this->genmat(value, value, t);
    m = value;
    k = value;
    n = value;
  }
  std::vector<float>& get_matrix_a() { return a; }
  std::vector<float>& get_matrix_b() { return b; }
  std::vector<float>& get_matrix_c() { return c; }
  std::vector<float>& get_matrix_t() { return t; }
  void thread_mat_mult(const std::vector<float>& mat_a, const std::vector<float>& mat_b, std::vector<float>& mat_c);
  void transpose_matrix(std::vector<float>& mat_b, std::vector<float>& mat_t);
  void original_mat_mult(std::vector<float>& mat_a, std::vector<float>& mat_b, std::vector<float>& mat_c);
  void genmat(int n, int m, std::vector<float>& mat);
  void dumpmat(std::vector<float>& mat);
};


#endif  // SVSLAM_MATRIX_MUL_HPP
