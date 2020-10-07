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
  std::cout << "STL std::generate sample\n";
  static constexpr int kArraySize{21};
  std::array<int, kArraySize> array{};
  auto fibonachi_generator = [a0 = 0, a1 = 1]() mutable {
    int next = a0 + a1;
    a0 = a1;
    a1 = next;
    return next;
  };
  std::cout << "generating fibonachi " << array.size() << " numbers\n";
  std::generate(array.begin(), array.end(), fibonachi_generator);
  auto print_int = [](int i) { std::cout << i << ' '; };
  std::for_each(array.begin(), array.end(), print_int);
  std::cout << '\n';
}
