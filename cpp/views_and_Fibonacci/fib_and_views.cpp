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

#include <ranges>
#include <iostream>
#include <vector>

auto square = [](size_t i) { return i * i; };

void fibonacci_generator(std::vector<size_t>& vtr) {
  vtr[0] = 0;
  vtr[1] = 1;
  vtr[2] = 1;
  for (size_t i = 3; i < vtr.size(); ++i) {
    vtr[i] = vtr[i - 2] + vtr[i - 1];
  }
  std::cout << "The generated sequence of the first " 
    << vtr.size() << " Fibonacci numbers is:" << std::endl;
  for (auto elem : std::span{ vtr.cbegin(), vtr.cbegin() + vtr.size() })
    std::cout << elem << " ";
  std::cout << std::endl;
}

void squaring_the_odds(std::vector<size_t>& vtr) 
{
  auto odd = [](size_t i) { return 0 != i % 2; };
  std::cout << "The squares of the odd numbers from the sequence are: " << std::endl;
  for (size_t i : vtr | std::views::filter(odd) | std::views::transform(square)) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;
}

void squaring_the_evens(std::vector<size_t>& vtr) 
{
  auto even = [](size_t i) { return 0 == i % 2; };
  std::cout << "The squares of the even numbers from the sequence are: " << std::endl;
  for (size_t i : vtr | std::views::filter(even) | std::views::transform(square)) {
    std::cout << i << ' ';
  }
  std::cout << std::endl;
}

int main()
{

  std::cout << "A little fun with Fibonacci and std::views." << std::endl;
  size_t N = 10;
  std::vector<size_t> fibonacci_vector(N);
  fibonacci_generator(fibonacci_vector);
  squaring_the_odds(fibonacci_vector);
  squaring_the_evens(fibonacci_vector);

  return 0;

}
