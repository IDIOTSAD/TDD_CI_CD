//
// Created by user on 22. 6. 7.
//

#include "module1/Matrix_mul.hpp"

int main()
{
  matrix_mul m(100);
  EASY_PROFILER_ENABLE;
  spdlog::info("Spdlog is activated!");
  std::cout << "cpu thread is = " << std::thread::hardware_concurrency() << '\n';
  const int iteration = 10000;
  EASY_BLOCK("Outer block", profiler::colors::Black);
  for (int i = 0; i < iteration; i++)
  {
    EASY_BLOCK("Inner block", profiler::colors::Green);
    m.original_mat_mult(m.get_matrix_a(), m.get_matrix_b(), m.get_matrix_c());
    EASY_END_BLOCK
  }
  EASY_END_BLOCK
  EASY_BLOCK("Thread_Outer block", profiler::colors::Black);
  // add transpose calculate time
  // m.transpose_matrix(m.get_matrix_b(), m.get_matrix_t());
  for (int i = 0; i < iteration; i++)
  {
    EASY_BLOCK("Thread_Inner block", profiler::colors::Green);
    m.thread_mat_mult(m.get_matrix_a(), m.get_matrix_t(), m.get_matrix_c());
    EASY_END_BLOCK
  }
  EASY_END_BLOCK

  m.dumpmat(m.get_matrix_a());
  m.dumpmat(m.get_matrix_c());
  EASY_END_BLOCK
  profiler::dumpBlocksToFile("../profiler_data/100x100_transform.prof");

  return 0;
}

// reference
// https://wiserloner.tistory.com/1277?category=825330 - cpu caching error (false sharing)
// https://junstar92.tistory.com/241 - matrix multiplication time compare (guide thread)