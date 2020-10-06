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
  std::cout << "STL std::transform samples\n";
  static constexpr std::array<int, 8> kInputArray{0, 1, 2, 3, 4, 5, 6, 7};
  std::cout << "transforming (unary increment by 1) [";
  auto print_int = [](int i) { std::cout << i << ' '; };
  std::for_each(kInputArray.begin(), kInputArray.end(), print_int);
  std::cout << "] to [";
  auto inc_by_1 = [](int i) { return i + 1; };
  std::array<int, kInputArray.size()> array{};
  std::transform(kInputArray.begin(), kInputArray.end(), array.begin(),
                 inc_by_1);
  std::for_each(array.begin(), array.end(), print_int);
  std::cout << "]\n";
  std::cout << "transforming (binary add) [";
  std::for_each(kInputArray.begin(), kInputArray.end(), print_int);
  std::cout << "] + [";
  std::for_each(array.begin(), array.end(), print_int);
  std::cout << "] = [";
  std::array<int, kInputArray.size()> sum{};
  auto add = [](int i0, int i1) { return i0 + i1; };
  std::transform(kInputArray.begin(), kInputArray.end(), array.begin(),
                 sum.begin(), add);
  std::for_each(sum.begin(), sum.end(), print_int);
  std::cout << "]\n";
  return 0;
}
