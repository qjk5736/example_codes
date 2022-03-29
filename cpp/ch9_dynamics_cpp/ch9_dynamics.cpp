// 
//   Copyright 2022 John I. Krassikoff
//   
//   This program is free software : you can redistribute it and /or modify
//   it under the terms of the GNU General Public License as published
//   by the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//   
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//   GNU General Public License for more details.
//   
//
//  This is an implementation of the algorithm in
//  The Feynman Lectures on Physics Vol. I Ch. 9
//  Newton's Laws of Mechanics, Section 9_6.
//

#define _CRT_SECURE_NO_WARNINGS

#include <tuple>
#include <vector>
#include <array>
#include <utility>
#include <iostream>

std::tuple<double, double, double> dynamics_update(double x,
  double v_t,
  double a_t,
  double t,
  double epsilon,
  bool first)
{
  double old_x = x;
  x = old_x + epsilon * v_t;
  a_t = -old_x;
  if (first == true)
    v_t = v_t + (epsilon / 2) * a_t;
  else
    v_t = v_t + epsilon * a_t;
  return { x, v_t, a_t };
}

void run_dynamics_update(std::vector < std::array<double, 5> >& results)
{
  double epsilon = 0.0100;  // seconds
  double max_time = 1.6;    // seconds
  int num_steps = int(round((max_time / epsilon) + 1));
  results.reserve(num_steps);
  std::array<double, 5> state = {0.0,0.0,0.0,0.0,0.0};
  double t = 0.0;         // seconds
  double v_t = 0.0;       // m/s
  double last_v_t = 0.0;  // m/s
  double a_t = 0.0;       // m/s^2
  double x = 1.0;         // m
  size_t idx = 0;
  bool first = true;
  while( t <= (max_time + epsilon))
  {
    std::tie(x, v_t, a_t) =dynamics_update(x, v_t, a_t, t, epsilon, first);
    state[0] = x;
    state[1] = v_t;
    state[2] = a_t;
    state[3] = t;
    state[4] = epsilon;
    results.push_back(state);
    first = false;
    idx += 1;
    t += epsilon;
  }
}

void print_results(std::vector < std::array<double, 5> >& results)
{
  FILE* fp = fopen("ch9_dynamics_data.dat", "w");
  if (!fp)
  {
    return;
  }
  fprintf(fp,"%s\t\t%s\t\t%s\t\t%s\n", " t", " x", " v_t", " a_t");
  for (auto &state : results)
  {
    fprintf(fp,"%3.2f\t\t%4.3f\t\t%4.3f\t\t%4.3f\n", state[3], state[0], state[1], state[2]);
  }
  fclose(fp);
}

int main()
{
  std::vector < std::array<double, 5> > results;
  run_dynamics_update(results);
  print_results(results);
}
