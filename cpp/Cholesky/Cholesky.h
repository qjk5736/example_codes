/*
Copyright (c) 2022 John I. Krassikoff

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


#ifndef Cholesky_H
#define Cholesky_H

#include <iostream>
#include <vector>
#include <cmath>
#include "Exception.h"

//
//  A template class for Cholesky decomposition of an 
//  square matrix of arbiutrary size. This decomposition 
//  can be used to test if the matrix is positive definite.
//  
//  Reference: Bronson, Matrix Operations, 1989
//

template <class T>
bool Cholesky(const std::vector<std::vector<T>> testArray, std::vector<std::vector<T>>& output)
{
  size_t sz = testArray.size();
  std::vector<std::vector<float> > L(sz, std::vector<float>(sz));
  size_t index = 0;
  size_t row = 0, col = 0;
  T factor = static_cast<T>(1);
  T sum = 0.0;
  T test_value = testArray[0][0];
  if (test_value <= static_cast<T>(0))
  {
    std::cerr << " Error! Ill-formed matrix in Choelsky function!" << std::endl;
    throw CholeskyException("ill-formed matrix");
  }
  factor = std::sqrt(testArray[0][0]);
  for (index = 0; index < sz; index++)
  {
    L[index][0] = testArray[index][0] / factor;
  }
  for (col = 1; col < sz; col++)
  {
    row = col;
    for (size_t s = 0; s < row; s++)
    {
      sum += L[row][s] * L[row][s];
    }
    test_value = testArray[row][col];
    if (test_value <= static_cast<T>(0))
    {
      std::cerr << " Error! Radicand is not positive!" << std::endl;
      throw CholeskyException("not_positive_definite");
    }
    L[row][col] = std::sqrt(test_value - sum);
    sum = 0.0;
    for (size_t s = row + 1; s < sz; s++)
    {
      for (size_t t = 0; t <= row; t++)
      {
        sum += L[s][t] * L[row][t];
      }
      L[s][col] = (testArray[s][col] - sum) / L[row][col];
      if (std::sqrt(L[s][col] * L[s][col]) < static_cast<T>(1E-12))
      {
        L[s][col] = static_cast<T>(0);
      }
      sum = static_cast<T>(0);
    }
  }
  for (row = 0; row < sz; row++)
  {
    for (col = 0; col < sz; col++)
    {
      output[row][col] = L[col][row];
    }
  }
  return true;
}


#endif /* Cholesky_H */
