//
// Copyright 2021 John I Krassikoff
//
// This program is free software : you can redistribute itand /or modify
// it under the terms of the GNU General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.If not, see < https://www.gnu.org/licenses/>.
//

#include "entropy_kernel_solver.h"
#include <iostream>
#include <memory>

int main(void)
{
  auto filtr = std::make_unique<entropy_kernel_solver>();
  const int num_of_elements = 49;
  // Kernal 1 gives an expected entropy value of ~5.5.
  int kernal1[num_of_elements] =
  {
    736,845,180,432,637,0,697,
    626,483,597,511,1018,219,289,
    683,879,766,569,373,190,659,
    179,679,483,541,692,660,366,
    297,857,420,713,491,932,944,
    443,590,479,585,710,474,549,
    585,390,278,1020,709,765,975
  };
  // Kernal 2 gives an entropy value of ~1.9.
  int kernal2[num_of_elements] =
  {
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 541, 944, 660, 366,
    0, 0, 0, 713, 944, 932, 944,
    0, 0, 0, 585, 710, 474, 549,
    0, 0, 0, 944, 709, 944, 975
  }; 
  std::cout << " Result for kernal 1: "; 
  std::cout << filtr->callEntropySolver(kernal1, num_of_elements) << std::endl;
  std::cout << " Result for kernal 2: ";
  std::cout << filtr->callEntropySolver(kernal2, num_of_elements) << std::endl;
  return 0;
}
