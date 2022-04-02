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

//#include <tuple>
#include <vector>
#include <array>
//#include <utility>
#include <iostream>

import newtonian_dynamics;

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
