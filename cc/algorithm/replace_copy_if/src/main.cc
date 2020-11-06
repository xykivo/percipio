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
  std::cout << "STL std::replace_copy_if sample\n";
  static constexpr int kArraySize{8};
  std::array<int, kArraySize> src_array{-1, 1, -2, 2, -3, 3, -4, 4};
  std::cout << "replace negative numbers from [";
  auto print_int = [](int i) { std::cout << i << ' '; };
  std::for_each(src_array.begin(), src_array.end(), print_int);
  static constexpr int kReplacement{0};
  std::cout << "] with " << kReplacement << " copied to [";
  auto is_negative = [](int i) { return (0 > i); };
  std::array<int, kArraySize> dst_array{};
  std::replace_copy_if(src_array.begin(), src_array.end(), dst_array.begin(),
                       is_negative, kReplacement);
  std::for_each(dst_array.begin(), dst_array.end(), print_int);
  std::cout << "]\n";
}
