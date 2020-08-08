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

/// Simple function that find an integer in a given range of integers
template <size_t ArraySize>
void FindIntInRange(const std::array<int, ArraySize>& array, int i) {
  if (array.end() != std::find(array.begin(), array.end(), i)) {
    std::cout << "Found ";
  } else {
    std::cout << "Did not find ";
  }
  std::cout << i << " in [";
  xykivo::percipio::util::OutputRange(std::cout, array.begin(), array.end(),
                                      " ");
  std::cout << "]\n";
}

}  // namespace

/// C++ find sample main entry point
int main() {
  std::cout << "STL std::find samples\n";
  static constexpr std::array<int, 8> kIntegerArray{0, 1, 2, 3, 4, 5, 6, 7};
  static constexpr int kIntInRange = 5;
  FindIntInRange(kIntegerArray, kIntInRange);
  static constexpr int kIntNotInRange = 8;
  FindIntInRange(kIntegerArray, kIntNotInRange);
  return 0;
}
