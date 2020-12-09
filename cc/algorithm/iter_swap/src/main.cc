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

/// C++ iter_swap main entry point
int main() {
  std::cout << "STL std::iter_swap sample\n";
  static constexpr size_t kArraySize{4};
  std::array<int, kArraySize> array_0{1, 2, 3, 4};
  std::array<int, kArraySize> array_1{-1, -2, -3, -4};
  std::cout << "swapping begin iterator of array_0=[";
  auto print_int = [](int i) { std::cout << i << ' '; };
  std::for_each(array_0.begin(), array_0.end(), print_int);
  std::cout << "] with begin iterator of array_1=[";
  std::for_each(array_1.begin(), array_1.end(), print_int);
  std::cout << "] -> ";
  std::iter_swap(array_0.begin(), array_1.begin());
  std::cout << " array_0=[";
  std::for_each(array_0.begin(), array_0.end(), print_int);
  std::cout << "] array_1=[";
  std::for_each(array_1.begin(), array_1.end(), print_int);
  std::cout << "]\n";
  return 0;
}
