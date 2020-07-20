// Copyright (C) 2020 Dror Smolarsky
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

#include "xykivo/percipio/util/out_stream.h"

namespace {

constexpr std::array<int, 8> kPositiveIntegers{1, 2, 3, 4, 5, 6, 7, 8};

/// Simple sampele of using for_each algorithm to negate a range of integers
template <size_t ArraySize>
void ForEachNegate(const std::array<int, ArraySize>& array) {
  std::vector<int> vec{};
  auto negate_into_vec = [&vec](int i) { vec.push_back(-1 * i); };
  std::for_each(array.begin(), array.end(), negate_into_vec);
  std::cout << "original array = ";
  xykivo::percipio::util::OutputRange(std::cout, array.begin(), array.end(),
                                      " ");
  std::cout << '\n';
  std::cout << "negated array values in vector = ";
  xykivo::percipio::util::OutputRange(std::cout, vec.begin(), vec.end(), " ");
  std::cout << '\n';
}

template <size_t ArraySize>
constexpr int Sum(const std::array<int, ArraySize>& array) {
  int sum = 0;
  auto add_to_sum = [&sum](int i) { sum += i; };
  std::for_each(array.begin(), array.end(), add_to_sum);
  return sum;
}

template <size_t ArraySize>
void ForEachSum(const std::array<int, ArraySize>& array) {
  std::cout << "The sum of ";
  xykivo::percipio::util::OutputRange(std::cout, array.begin(), array.end(),
                                      " ");
  std::cout << " = " << Sum(array) << '\n';
}

}  // namespace

/// C++ for_each main entry point
int main() {
  std::cout << "STL std::none_of samples\n";
  ForEachNegate(kPositiveIntegers);
  ForEachSum(kPositiveIntegers);
  return 0;
}
