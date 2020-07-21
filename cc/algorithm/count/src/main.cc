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

/// Simple function that uses std::count algorithm to count how many time an
/// integer appears in an array of integers
template <size_t ArraySize>
void CountInt(const std::array<int, ArraySize>& array, int i) {
  std::cout << i << " appears " << std::count(array.begin(), array.end(), i)
            << " times in ";
  xykivo::percipio::util::OutputRange(std::cout, array.begin(), array.end(),
                                      " ");
  std::cout << '\n';
}

}  // namespace

/// C++ for_each main entry point
int main() {
  std::cout << "STL std::count samples\n";
  static constexpr std::array<int, 10> kIntegerArray{1, 2, 2, 3, 3,
                                                     3, 4, 4, 4, 4};
  static constexpr int kMaxIntCounted = 4;
  for (int i = 0; kMaxIntCounted > i; ++i) {
    CountInt(kIntegerArray, i);
  }
  return 0;
}
