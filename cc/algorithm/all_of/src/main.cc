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
#include <iterator>

namespace {

static constexpr std::array<int, 8> kPositiveIntegers{1, 2, 3, 4, 5, 6, 7, 8};

static constexpr std::array<int, 8> kPositiveAndNegativeIntegers{-1, 1, -2, 2,
                                                                 -3, 3, -4, 4};

template <size_t ArraySize>
void simple_all_off(const std::array<int, ArraySize> array) {
  auto is_positive = [](int i) { return (0 < i); };
  if (std::all_of(array.begin(), array.end(), is_positive)) {
    std::cout << "All integers in ";
    std::copy(array.begin(), array.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << " are positive\n";
  } else {
    std::cout << "Not all integers in ";
    std::copy(array.begin(), array.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << " are positive\n";
  }
}

}  // namespace

/// C++ all_of main entry point
int main() {
  std::cout << "STL std::all_of samples\n";
  simple_all_off(kPositiveIntegers);
  simple_all_off(kPositiveAndNegativeIntegers);
  return 0;
}
