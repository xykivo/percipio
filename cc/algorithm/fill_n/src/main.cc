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

int main() {
  std::cout << "STL std::fill_n samples\n";
  static constexpr size_t kArraySize{8};
  std::array<int, kArraySize> array{};
  std::cout << "Initialized array [";
  auto print_int = [](int i) { std::cout << i << ' '; };
  std::for_each(array.begin(), array.end(), print_int);
  std::cout << "]\n";
  for (size_t i = 0; kArraySize > i; ++i) {
    std::fill_n(array.begin(), array.size() / 2, i);
    std::cout << "Filled " << array.size() / 2 << " elements of array with "
              << i << " [";
    std::for_each(array.begin(), array.end(), print_int);
    std::cout << "]\n";
  }
  return 0;
}
