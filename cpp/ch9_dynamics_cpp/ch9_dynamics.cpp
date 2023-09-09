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
