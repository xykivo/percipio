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

/// Simple funciton that finds 2 adjacent integers that are equal in the given
/// integer array
template <size_t ArraySize>
void FindAdjacentEqualIntegers(const std::array<int, ArraySize>& array) {
  auto iter = std::adjacent_find(array.begin(), array.end());
  if (array.end() == iter) {
    std::cout << "No two adjacent equal integers found in [";
  } else {
    std::cout << "Found 2 adjacent integers equal to " << *iter << " in [";
  }
  xykivo::percipio::util::OutputRange(std::cout, array.begin(), array.end(),
                                      " ");
  std::cout << "]\n";
}

}  // namespace

/// C++ std::adjacent_find sample main entry point
int main() {
  std::cout << "STL std::fadjacent_find samples\n";
  static constexpr std::array<int, 8> kIntegerArrayo{0, 1, 2, 3, 4, 4, 5, 6};
  FindAdjacentEqualIntegers(kIntegerArrayo);
  static constexpr std::array<int, 8> kIntegerArray1{0, 1, 2, 3, 4, 5, 6, 7};
  FindAdjacentEqualIntegers(kIntegerArray1);
  return 0;
}
