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
#include <random>

/// C++ sample algorithm main entry point
int main() {
  std::cout << "STL std::sample example\n";
  static constexpr size_t kArraySize{16};
  std::array<int, kArraySize> src_array{
      0, 1, 2,  3,  4,  5,  6,  7,    // NOLINT(readability-magic-numbers)
      8, 9, 10, 11, 12, 13, 14, 15};  // NOLINT(readability-magic-numbers)
  std::array<int, src_array.size() / 3> dst_array{};
  std::cout << "Sampling " << dst_array.size() << " elements of array=[";
  auto print_int = [](int i) { std::cout << i << ' '; };
  std::for_each(src_array.begin(), src_array.end(), print_int);
  std::sample(src_array.begin(), src_array.end(), dst_array.begin(),
              dst_array.size(), std::mt19937{std::random_device{}()});
  std::cout << "] -> array=[";
  std::for_each(dst_array.begin(), dst_array.end(), print_int);
  std::cout << "]\n";
  return 0;
}
