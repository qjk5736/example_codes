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

#ifndef Choelsky_H
#define Choelsky_H

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
bool Choelsky(const std::vector<std::vector<T>> testArray, std::vector<std::vector<T>>& output)
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
    throw ChoelskyException("ill-formed matrix");
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
      throw ChoelskyException("not_positive_definite");
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


#endif /* Choelsky_H */
