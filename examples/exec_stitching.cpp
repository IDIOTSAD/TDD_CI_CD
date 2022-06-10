//
// Created by changh95 on 5/26/22.
//

#include "module2/Stitching.hpp"

int main()
{
  EASY_PROFILER_ENABLE;
  spdlog::info("Spdlog is activated!");
  EASY_BLOCK("Outer block", profiler::colors::Black);

  stitch s;
  bool is_load = s.input_pictures("../img1.jpg", "../img2.jpg");
  if (!is_load) {
    return -1;
  }
  s.cal_descripter("ORB");
  s.cal_good_matches(20);
  s.show_feature();

  EASY_END_BLOCK
  profiler::dumpBlocksToFile("../test_profile.prof");
  return 0;
}