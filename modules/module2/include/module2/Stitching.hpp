//
// Created by user on 22. 6. 10.
//

#ifndef SVSLAM_STITCHING_HPP
#define SVSLAM_STITCHING_HPP

#define USING_EASY_PROFILER
#include "easy/profiler.h"
#include "spdlog/spdlog.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>

class stitch
{
private:
  cv::Mat img1;
  cv::Mat img2;
  cv::Ptr<cv::Feature2D> detector;
  std::vector<cv::KeyPoint> keypoints1, keypoints2;
  cv::Mat descriptors1, descriptors2;
  cv::FlannBasedMatcher Matcher;
  std::vector<cv::DMatch> matches;
  cv::Mat matGoodMatches;
  std::vector<cv::DMatch> good_matches;
  std::vector<cv::Point2f> obj;
  std::vector<cv::Point2f> scene;
  cv::Mat HomoMatrix;
  cv::Mat matResult;
public:
  bool input_pictures(const std::string& image1, std::string image2);
  bool input_pictures_filp(const std::string& image1, std::string image2);
  bool input_pictures(cv::Mat image1, cv::Mat image2);
  bool input_pictures(const std::string& image1, cv::Mat image2);
  bool input_pictures(cv::Mat image1, const std::string& image2);

  void cal_descripter(const std::string& name);
  void cal_good_matches(int num);
  void show_feature();
  cv::Mat getResult();
  void show_feature_flip();
};

#endif  // SVSLAM_STITCHING_HPP
