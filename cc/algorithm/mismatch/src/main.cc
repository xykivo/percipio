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

/// Simple function that uses std::mistmatch algorithm to compare 2 integer
/// array, and find the 1st mismatching integer.
template <size_t ArraySize>
void CompareRangeMismatch(const std::array<int, ArraySize>& array_0,
                          const std::array<int, ArraySize>& array_1) {
  std::cout << "comparing\n\t";
  xykivo::percipio::util::OutputRange(std::cout, array_0.begin(), array_0.end(),
                                      " ");
  std::cout << "\n\t";
  xykivo::percipio::util::OutputRange(std::cout, array_1.begin(), array_1.end(),
                                      " ");
  std::cout << '\n';
  auto not_equal = std::mismatch(array_0.begin(), array_0.end(),
                                 array_1.begin(), array_1.end());
  if (not_equal.first == array_0.end()) {
    std::cout << "\tall elements are equal\n";
  } else {
    std::cout << '\t' << *(not_equal.first) << " != " << *(not_equal.second)
              << '\n';
  }
  std::cout << '\n';
}

/// Simple function that uses std::mistmatch algorithm to find the first pair
/// of elements from 2 arrays, where at least one of the elements is less than
/// 0.
template <size_t ArraySize>
void IsLessThan0RangeMismatch(const std::array<int, ArraySize>& array_0,
                              const std::array<int, ArraySize>& array_1) {
  std::cout << "comparing\n\t";
  xykivo::percipio::util::OutputRange(std::cout, array_0.begin(), array_0.end(),
                                      " ");
  std::cout << "\n\t";
  xykivo::percipio::util::OutputRange(std::cout, array_1.begin(), array_1.end(),
                                      " ");
  std::cout << '\n';
  // The predicate returns true if there is no mismtach, and false if there is
  // a mismatch
  auto less_than_0_predicate = [](int i0, int i1) {
    return ((0 <= i0) && (0 <= i1));
  };
  auto is_less_than_0 =
      std::mismatch(array_0.begin(), array_0.end(), array_1.begin(),
                    array_1.end(), less_than_0_predicate);
  if (is_less_than_0.first == array_0.end()) {
    std::cout << "\tall elements greater than 0\n";
  } else {
    std::cout << '\t' << *(is_less_than_0.first) << " is less than 0,  or "
              << *(is_less_than_0.second) << " is less than 0\n";
  }
  std::cout << '\n';
}

}  // namespace

/// C++ mismatch main entry point
int main() {
  std::cout << "STL std::mismatch samples\n";
  static constexpr std::array<int, 8> kIntegerArray0{0, 1, 2, 3, 4, 5, 6, 7};
  static constexpr std::array<int, 8> kIntegerArray1{0, 1, 2, 3, 14, -5, 6, 7};
  CompareRangeMismatch(kIntegerArray0, kIntegerArray1);
  CompareRangeMismatch(kIntegerArray0, kIntegerArray0);
  IsLessThan0RangeMismatch(kIntegerArray0, kIntegerArray1);
  static constexpr std::array<int, 8> kIntegerArray2{0, 1, 2, 3, 14, 15, 6, 7};
  IsLessThan0RangeMismatch(kIntegerArray0, kIntegerArray2);
  return 0;
}
