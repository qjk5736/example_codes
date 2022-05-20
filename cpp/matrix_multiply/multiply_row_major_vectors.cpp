//
// Copyright 2022 John I. Krassikoff
//
// This program is free software : you can redistribute itand /or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.If not, see < https://www.gnu.org/licenses/>.
//
// multipy_row_major_vectors.cpp 
// Performs the mulitplication of arbitrarily sized matrices represented 
// as row major vectors. The multiplication is timed using chrono.
//

#include <iostream>
#include <vector>
#include <cstring>
#include <chrono> 
using namespace std::chrono;

void multiply_two_matrices(std::vector<double> mat1, std::vector<double> mat2, std::vector<double>& mat3)
{
  size_t dims = static_cast<size_t>(std::sqrt(mat1.size()));
  for (int col = 0; col < dims; col++)
  {
    for (int row = 0; row < dims; row++)
    {
      mat3[col + row*dims] = mat1[col + row * dims] * mat2[col + row * dims];
    }
  }
}

void plot_vector_as_matrix(std::vector<double>& mat, std::string descr)
{
  std::cout << descr << std::endl << std::endl;
  size_t dims = static_cast<size_t>(std::sqrt(mat.size()));
  for (int row = 0; row < dims; row++)
  {
    for (int col = 0; col < dims; col++)
    {
      std::cout << mat[col + row * dims];
      if (col != (dims-1))
      {
        std::cout << ", ";
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void run()
{
  //
  // ROW MAJOR vectors represent the matrices.
  //
  {
    std::vector<double> mat1 = { 1.0, 4.0, 3.0, 2.0 };
    std::vector<double> mat2 = { 5.0, 8.0, 7.0, 6.0 };
    std::vector<double>  mat3(4, 0);
    plot_vector_as_matrix(mat1, "2x2 mat1");
    plot_vector_as_matrix(mat2, "2x2 mat2");
    auto start = high_resolution_clock::now();
    multiply_two_matrices(std::move(mat1), std::move(mat2), mat3);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "The time to perform multiplication of a pair of 2x2 matrices: "
      << duration.count() << " microseconds" << std::endl;
    std::cout << std::endl;
    plot_vector_as_matrix(mat3, "2x2 mat1*mat2");
  }
  {
    std::vector<double> mat1 = { 1.0, 4.0, 3.0, 2.0, 1.0, 4.0, 3.0, 2.0, 2.0 };
    std::vector<double> mat2 = { 5.0, 8.0, 7.0, 6.0, 5.0, 8.0, 7.0, 6.0, 8.0 };
    std::vector<double>  mat3(9, 0);
    plot_vector_as_matrix(mat1, "3x3 mat1");
    plot_vector_as_matrix(mat2, "3x3 mat2");
    auto start = high_resolution_clock::now();
    multiply_two_matrices(std::move(mat1), std::move(mat2), mat3);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "The time to perform multiplication of a pair of 3x3 matrices: "
      << duration.count() << " microseconds" << std::endl;
    std::cout << std::endl;
    plot_vector_as_matrix(mat3, "3x3 mat1*mat2");
  }
}

int main()
{
  run();
  return 0;
}
