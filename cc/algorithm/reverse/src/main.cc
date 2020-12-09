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

/// C++ reverse main entry point
int main() {
  std::cout << "STL std::reverse sample\n";
  static constexpr size_t kArraySize{8};
  // NOLINTNEXTLINE(readability-magic-numbers)
  std::array<int, kArraySize> array{0, 1, 2, 3, 4, 5, 6, 7};
  std::cout << "Reversing array=[";
  auto print_int = [](int i) { std::cout << i << ' '; };
  std::for_each(array.begin(), array.end(), print_int);
  std::cout << "] -> ";
  std::reverse(array.begin(), array.end());
  std::cout << " array=[";
  std::for_each(array.begin(), array.end(), print_int);
  std::cout << "]\n";
  return 0;
}
