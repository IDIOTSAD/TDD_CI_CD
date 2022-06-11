//
// Created by user on 22. 6. 10.
//

#include "module2/Stitching.hpp"

#include <utility>

bool stitch::input_pictures(const std::string& image1, std::string image2) {
  img1 = cv::imread(image1);
  img2 = cv::imread(image2);

  if (img1.empty() || img2.empty())
  {
    std::cerr << "Image load failed!" << "\n";
    return false;
  }
  return true;
}

bool stitch::input_pictures_filp(const std::string& image1, std::string image2) {
  img1 = cv::imread(image2);
  img2 = cv::imread(image1);

  cv::flip(img1, img1, 1);
  cv::flip(img2, img2, 1);

  if (img1.empty() || img2.empty())
  {
    std::cerr << "Image load failed!" << "\n";
    return false;
  }
  return true;
}

bool stitch::input_pictures(const std::string& image1, cv::Mat image2) {
  img1 = cv::imread(image1);
  img2 = std::move(image2);
  if (img1.empty() || img2.empty())
  {
    std::cerr << "Image load failed!" << "\n";
    return false;
  }
  return true;
}

bool stitch::input_pictures(cv::Mat image1, const std::string& image2) {
  img1 = std::move(image1);
  img2 = cv::imread(image2);
  if (img1.empty() || img2.empty())
  {
    std::cerr << "Image load failed!" << "\n";
    return false;
  }
  return true;
}

bool stitch::input_pictures(cv::Mat image1, cv::Mat image2) {
  img1 = std::move(image1);
  img2 = std::move(image2);
  if (img1.empty() || img2.empty())
  {
    std::cerr << "Image load failed!" << "\n";
    return false;
  }
  return true;
}

void stitch::cal_descripter(const std::string& name) {
  if (name == "ORB" || name == "ORB") {
    detector = cv::ORB::create(400);
  }
  else if (name == "AKAZE" || name =="akaze") {
    detector = cv::AKAZE::create();
  }
  else {
    detector = cv::SIFT::create(400);
  }
  detector->detectAndCompute(img1, cv::Mat(), keypoints1, descriptors1);
  detector->detectAndCompute(img2, cv::Mat(), keypoints2, descriptors2);
  // https://stackoverflow.com/questions/29694490/flann-error-in-opencv-3
  if(descriptors1.type()!=CV_32F) {
    descriptors1.convertTo(descriptors1, CV_32F);
  }

  if(descriptors2.type()!=CV_32F) {
    descriptors2.convertTo(descriptors2, CV_32F);
  }
}

void stitch::cal_good_matches(int count) {
  Matcher.match(descriptors1, descriptors2, matches);
  std::sort(matches.begin(), matches.end(), [](cv::DMatch &a, cv::DMatch &b) {
              return (a.distance < b.distance);
            });
  for (int i = 0; i < count; i++)
  {
    good_matches.push_back(matches[i]);
  }
  for (auto & good_matche : good_matches)
  {
    obj.push_back(keypoints1[good_matche.queryIdx].pt);
    scene.push_back(keypoints2[good_matche.trainIdx].pt);
  }
}

void stitch::show_feature() {
  drawMatches(img1, keypoints1, img2, keypoints2, good_matches, matGoodMatches, cv::Scalar::all(-1), cv::Scalar(-1), std::vector<char>(), cv::DrawMatchesFlags::DEFAULT);
  cv::imshow("good-matches", matGoodMatches);
  HomoMatrix = findHomography(scene, obj, cv::RANSAC);
  warpPerspective(img2, img2, HomoMatrix, cv::Size(img1.cols * 2, img1.rows), cv::INTER_CUBIC);
  cv::Mat matROI(img2, cv::Rect(0, 0, img1.cols, img1.rows));
  img1.copyTo(matROI);
  matResult = img2;
  imshow("Panorama", matResult);
  cv::waitKey(0);
}

void stitch::show_feature_flip() {
  drawMatches(img1, keypoints1, img2, keypoints2, good_matches, matGoodMatches, cv::Scalar::all(-1), cv::Scalar(-1), std::vector<char>(), cv::DrawMatchesFlags::DEFAULT);
  cv::imshow("good-matches", matGoodMatches);
  HomoMatrix = findHomography(scene, obj, cv::RANSAC);
  warpPerspective(img2, img2, HomoMatrix, cv::Size(img1.cols * 2, img1.rows), cv::INTER_CUBIC);
  cv::Mat matROI(img2, cv::Rect(0, 0, img1.cols, img1.rows));
  img1.copyTo(matROI);
  matResult = img2;
  cv::flip(matResult, matResult, 1);
  imshow("Panorama", matResult);
  cv::waitKey(0);
}

cv::Mat stitch::getResult() {
  return this->matResult;
}