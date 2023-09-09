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

//
//  Really simple code with OpenMP and mutex lock_guard.
// 
//  filename simple_OMP.cpp
// 

#include <omp.h>
#include <iostream>
#include <mutex>
#include <vector>
#include <cmath>

std::mutex m;

template <typename T> T calculate_exp_id(T x)
{
  return std::exp(x);
}

void print_tuples(std::vector<std::tuple<int, double> > tuples){
	std::cout << " Total number of threads requested: " << tuples.size() << "\n" << std::endl;
  std::cout << " thread_id\texp(thread_id)" << "\n" << std::endl;
  for (auto currentTuple : tuples) {
    std::cout << '\t' << std::get<0>(currentTuple) << '\t';
    std::cout << std::get<1>(currentTuple) << '\n';
  }
  std::cout << std::endl;
  tuples.clear();
}

void run(int n){
	int thread_id = -1;
  double t_value = 0.;
  std::vector<std::tuple<int, double> > data_tuple;
	#pragma omp parallel private(thread_id) num_threads(n)
	{
    const std::lock_guard<std::mutex> lock(m);
		thread_id = omp_get_thread_num();
    t_value = calculate_exp_id(static_cast<double>(thread_id));
    data_tuple.push_back(std::make_tuple(thread_id, t_value));
	}
  print_tuples(std::move(data_tuple));
}

int main()
{
	std::cout << " Running the simple OMP program." << std::endl;
  int number_requested_threads = 5;
  run(number_requested_threads);
	std::cout << " Program complete." << std::endl;
	return 0;
}