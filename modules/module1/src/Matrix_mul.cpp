//
// Created by changh95 on 5/26/22.
//

#include "module1/Matrix_mul.hpp"

void original_mat_mult(std::vector<float>& mat_a, std::vector<float>& mat_b, std::vector<float>& mat_c);
void genmat(int n, int m, std::vector<float>& mat);
void dumpmat(int n, int m, std::vector<float>& mat);
// Homework - Make a mat_mult function which is faster than this one!
void matrix_mul::thread_mat_mult(const std::vector<float>& mat_a, const std::vector<float>& mat_b, std::vector<float>& mat_c)
{
  /*
      Input:
      mat_a: m x k matrix
      mat_b: k x n matrix

      Output:
      mat_c: m x n matrix (output)
  */
  unsigned int thread = std::thread::hardware_concurrency();
  std::vector<std::thread> workers;
  int first = 0;
  int step = int(m / thread);
  int last = step;

  auto work_function = [&](int start, int end)
  {
    for (int i1 = start; i1 < end; i1++)
    {
      for (int i2 = 0; i2 < n; i2++)
      {
        mat_c[n * i1 + i2] = 0;
        for (int i3 = 0; i3 < k; i3++)
        {
          mat_c[n * i1 + i2] += mat_a[i1 * k + i3] * mat_b[i3 * n + i2];
        }
      }
    }
  };

  for (unsigned int i = 0; i < thread; i++)
  {
    first = step * i;
    last = std::min(first + step, m);
    workers.emplace_back(std::thread(work_function, first, last));
  }

  for(unsigned int i = 0; i < thread; i++)
  {
    workers[i].join();
  }
}

void matrix_mul::transpose_matrix(std::vector<float>& mat_b, std::vector<float>& mat_t)
{
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < n; j++) {
      mat_t[j * k + i] = mat_b[i * n + j];
    }
  }
}

void matrix_mul::original_mat_mult(std::vector<float>& mat_a, std::vector<float>& mat_b, std::vector<float>& mat_c)
{
  for (int i1=0; i1<m; i1++)
  {
    for (int i2=0; i2<n; i2++)
    {
      mat_c [n*i1 + i2] = 0;
      for (int i3=0; i3<k; i3++)
      {
        mat_c[n*i1 + i2] += mat_a[i1 * k + i3] * mat_b[i3 * n + i2];
      }
    }
  }
}

//clangformat is not recommand srand, rand.
void matrix_mul::genmat(int nn, int mm, std::vector<float>& mat)
{ /*
  std::random_device rd;
  mat.resize(n * m);
  for (float& i : mat) i = float(rd() % 100);
  */
  srand(time(0));
  mat.resize(nn * mm);
  for (int i = 0; i < int(mat.size()); i++)
  {
    mat[i] = rand() % 100;
  }
}

void matrix_mul::dumpmat(std::vector<float>& mat)
{
  for (int i=0; i<n; i++)
  {
    for (int j=0; j<m; j++)
      printf("%f ", mat[i * m + j]);
    printf("\n");
  }
}