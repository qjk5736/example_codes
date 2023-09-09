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
