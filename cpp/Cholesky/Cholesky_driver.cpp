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

#include <iostream>
#include <vector>
#include <string>
#include "Cholesky.h"

int main()
{
  bool success = false;
  std::cout << "Running Cholesky Decomposition using std::vectors.\n";
  std::vector<std::vector<float>> vect_inp
  {
      {2., -1., 0.},
      {-1., 2., -1.},
      {0., -1., 2.}
  };
  std::cout << "Input vector." << std::endl;
  for (size_t i = 0; i < vect_inp.size(); i++)
  {
    for (size_t j = 0; j < vect_inp[i].size(); j++)
    {
      std::cout << "\t" << vect_inp[i][j];
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  std::vector<std::vector<float> > vect_res(3, std::vector<float>(3) );
  try
  {
    success = Cholesky(std::move(vect_inp), vect_res);
    std::cout << "Output vector." << std::endl;
    for (size_t i = 0; i < vect_res.size(); i++)
    {
      for (size_t j = 0; j < vect_res[i].size(); j++)
      {
        std::cout << "\t" << vect_res[i][j];
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }
  catch (CholeskyException& e)
  {
    std::cout << e.getMessage() << std::endl;
    // Do nothing else. Success is already false.
  }
  return !success;
}
