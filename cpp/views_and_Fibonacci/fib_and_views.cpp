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
