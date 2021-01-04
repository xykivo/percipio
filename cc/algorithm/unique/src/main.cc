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

/// C++ sample algorithm main entry point
int main() {
  std::cout << "STL std::unique example\n";
  static constexpr size_t kArraySize{16};
  std::array<int, kArraySize> array{
      0, 1, 2, 2, 3, 3, 3, 4,   // NOLINT(readability-magic-numbers)
      4, 4, 4, 5, 5, 5, 5, 5};  // NOLINT(readability-magic-numbers)
  std::cout << "Equality unique - array=[";
  auto print_int = [](int i) { std::cout << i << ' '; };
  std::for_each(array.begin(), array.end(), print_int);
  auto unique_array_end = std::unique(array.begin(), array.end());
  std::cout << "] -> array=[";
  std::for_each(array.begin(), unique_array_end, print_int);
  std::cout << "]\n";

  std::cout << "Predicate (equal LSB) unique - array=[";
  array = {0, 1, 3, 5, 7, 2, 4, 6,   // NOLINT(readability-magic-numbers)
           8, 1, 2, 3, 4, 5, 6, 7};  // NOLINT(readability-magic-numbers)
  std::for_each(array.begin(), array.end(), print_int);
  auto equal_lsb = [](int i0, int i1) {
    static constexpr int kLsbMask{0x1};
    return ((i0 & kLsbMask) == (i1 & kLsbMask));
  };
  unique_array_end = std::unique(array.begin(), array.end(), equal_lsb);
  std::cout << "] -> array=[";
  std::for_each(array.begin(), unique_array_end, print_int);
  std::cout << "]\n";

  return 0;
}
