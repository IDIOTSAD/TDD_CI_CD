//
// Created by changh95 on 5/26/22.
//

#include "module2/Stitching.hpp"

int main()
{
  EASY_PROFILER_ENABLE;
  spdlog::info("Spdlog is activated!");
  EASY_BLOCK("Outer block", profiler::colors::Black);
  // two picture panorama
  /*
  stitch s;
  bool is_load = s.input_pictures("../img1.jpg", "../img2.jpg");
  if (!is_load) {
    return -1;
  }
  s.cal_descripter("ORB");
  s.cal_good_matches(20);
  s.show_feature();
  */

  // three picture panorama
  stitch s3;
  bool is_load3 = s3.input_pictures_filp("../img1.jpg", "../img2.jpg");
  if (!is_load3) {
    return -1;
  }

  s3.cal_descripter("ORB");
  s3.cal_good_matches(10);
  s3.show_feature_flip();
  cv::Mat left = s3.getResult();

  is_load3 = s3.input_pictures("../img2.jpg", "../img3.jpg");
  if (!is_load3) {
    return -1;
  }
  s3.cal_descripter("ORB");
  s3.cal_good_matches(10);
  s3.show_feature();
  cv::Mat right = s3.getResult();

  is_load3 = s3.input_pictures(left, right);
  if (!is_load3) {
    return -1;
  }
  s3.cal_descripter("ORB");
  s3.cal_good_matches(10);
  s3.show_feature();

  EASY_END_BLOCK
  profiler::dumpBlocksToFile("../ORB.prof");
  return 0;
}