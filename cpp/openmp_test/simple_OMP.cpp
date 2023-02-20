// 
//   Copyright 2023 John I. Krassikoff
//   
//   This program is free software : you can redistribute it and /or modify
//   it under the terms of the GNU General Public License as published
//   by the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//   
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PUR_posE.See the
//   GNU General Public License for more details.
//   
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