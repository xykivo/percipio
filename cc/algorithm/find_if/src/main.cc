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

#include "xykivo/percipio/util/out_stream.h"

namespace {

/// Simple function that finds the 1st integer in a given range of integers
/// that is greater than a given integer
template <size_t ArraySize>
void FindIntGreaterThanInRange(const std::array<int, ArraySize>& array, int i) {
  auto greater_than = [&i](int j) { return (j > i); };
  auto greater_than_i = std::find_if(array.begin(), array.end(), greater_than);
  if (array.end() != greater_than_i) {
    std::cout << *greater_than_i << " is greater than ";
  } else {
    std::cout << "No integer greater than ";
  }
  std::cout << i << " in [";
  xykivo::percipio::util::OutputRange(std::cout, array.begin(), array.end(),
                                      " ");
  std::cout << "]\n";
}

}  // namespace

/// C++ std::find_if sample main entry point
int main() {
  std::cout << "STL std::find_if samples\n";
  static constexpr std::array<int, 8> kIntegerArray{0, 1, 2, 3, 4, 5, 6, 7};
  static constexpr int kSmallInt = 5;
  FindIntGreaterThanInRange(kIntegerArray, kSmallInt);
  static constexpr int kLargeInt = 8;
  FindIntGreaterThanInRange(kIntegerArray, kLargeInt);
  return 0;
}
