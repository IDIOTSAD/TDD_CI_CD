//
// Created by user on 22. 6. 10.
//

#include "module2/Stitching.hpp"

bool stitch::input_pictures(std::string image1, std::string image2) {
  img1 = cv::imread(image1);
  img2 = cv::imread(image2);
  if (img1.empty() || img2.empty())
  {
    std::cerr << "Image load failed!" << "\n";
    return false;
  }
  return true;
}

void stitch::cal_descripter(std::string name) {
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
  for (int i = 0; i < int(good_matches.size()); i++)
  {
    obj.push_back(keypoints1[good_matches[i].queryIdx].pt);
    scene.push_back(keypoints2[good_matches[i].trainIdx].pt);
  }
}

void stitch::show_feature() {
  drawMatches(img1, keypoints1, img2, keypoints2, good_matches, matGoodMatches, cv::Scalar::all(-1), cv::Scalar(-1), std::vector<char>(), cv::DrawMatchesFlags::DEFAULT);
  cv::imshow("good-matches", matGoodMatches);
  HomoMatrix = findHomography(scene, obj, cv::RANSAC);
  warpPerspective(img2, matResult, HomoMatrix, cv::Size(img2.cols * 2, img2.rows), cv::INTER_CUBIC);
  imshow("result", matResult);
  cv::waitKey(0);
}