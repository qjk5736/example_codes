//
// Copyright 2021 John I. Krassikoff
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
#include <array>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
#include "alpha_beta_filter.h"

void printStateList(std::list<std::array<double, 4>> list) {
  for (auto i : list) {
    std::cout << "\tx: " << i[0];
    std::cout << "\tdx: " << i[1];
    std::cout << "\ty: " << i[2];
    std::cout << "\tdy: " << i[3] << std::endl;
  }
}

int main()
{
  std::cout << "Starting the alpha-beta-filter test.\n" << std::endl;
  auto abf = std::make_unique<alpha_beta_filter>();
  const int number_of_measurements = 10;
  std::array<double, 4> state = { {0, 0, 0, 0} };
  std::list<std::array<double, 4>> state_list;
  std::array<double, number_of_measurements> measurementsX = { {  -1.77 , -0.78 , -1.28 , -1.06 , -3.65 , -2.47 , -0.06 , -0.91 , -0.80 , 1.48 } };
  {
    std::cout << "measurementsX: ";
    for (auto i : measurementsX) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  }
  std::array<double, number_of_measurements> measurementsY = { {  -1.77 , -0.78 , -1.28 , -1.06 , -3.65 , -2.47 , -0.06 , -0.91 , -0.80 , 1.48 } };
  std::reverse(measurementsY.begin(), measurementsY.begin() + 9); // number_of_measurements);
  {
    std::cout << "measurementsY: ";
    for (auto i : measurementsY) {
      std::cout << i << " ";
    }
    std::cout << std::endl << "\nFilter output" << std::endl;;
  }
  std::cout << std::endl;
  double x0 = -1.0;
  double y0 = -1.0;
  double dt = 0.01;
  double initial_x = (x0 + measurementsX[1]) / 2.0;
  double initial_y = (y0 + measurementsY[1]) / 2.0;
  double initial_vx = 0.0, initial_vy = 0.0;
  double initial_ax = 0.0, initial_ay = 0.0;
  abf->initialize(dt, initial_x, initial_vx, initial_y, initial_vy);
  // for (auto i : measurementsX, auto j : measurementsY) {
  for (auto idx = 0; idx < number_of_measurements; ++idx){ // : measurementsX, auto j : measurementsY)
    state_list.push_back(abf->update(measurementsX[idx], measurementsY[idx], std::move(state)));
  }
  printStateList(std::move(state_list));
  std::cout << "\nThe alpha-beta-filter test is complete." << std::endl;
  return 0;
}
