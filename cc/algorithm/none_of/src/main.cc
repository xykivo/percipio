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
#include <string_view>

#include "xykivo/percipio/util/out_stream.h"

namespace {

constexpr std::array<int, 8> kPositiveIntegers{1, 2, 3, 4, 5, 6, 7, 8};

constexpr std::array<int, 8> kPositiveAndNegativeIntegers{-1, 1, -2, 2,
                                                          -3, 3, -4, 4};

constexpr std::array<int, 8> kNegativeIntegers{-1, -2, -3, -4, -5, -6, -7, -8};

template <size_t ArraySize>
void SimpleNoneOf(const std::array<int, ArraySize>& array) {
  auto is_positive = [](int i) { return (0 < i); };
  if (std::none_of(array.begin(), array.end(), is_positive)) {
    std::cout << "None of the integers in [";
    xykivo::percipio::util::OutputRange(std::cout, array.begin(), array.end(),
                                        " ");
    std::cout << "] are positive\n";
  } else {
    std::cout << "Some of the integers in [";
    xykivo::percipio::util::OutputRange(std::cout, array.begin(), array.end(),
                                        " ");
    std::cout << "] are positive\n";
  }
}

}  // namespace

/// C++ all_of main entry point
int main() {
  std::cout << "STL std::none_of samples\n";
  SimpleNoneOf(kPositiveIntegers);
  SimpleNoneOf(kPositiveAndNegativeIntegers);
  SimpleNoneOf(kNegativeIntegers);
  return 0;
}
