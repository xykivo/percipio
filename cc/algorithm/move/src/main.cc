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
#include <memory>

/// C++ move main entry point
int main() {
  std::cout << "STL std::move samples\n";
  static constexpr size_t kArraySize{4};
  std::array<std::unique_ptr<int>, kArraySize> src_array{
      std::make_unique<int>(0), std::make_unique<int>(1),
      std::make_unique<int>(2), std::make_unique<int>(3)};
  std::cout << "Moved [";
  auto print_unique_int_ptr = [](const std::unique_ptr<int>& int_ptr) {
    if (nullptr == int_ptr) {
      std::cout << "nullptr ";
    } else {
      std::cout << *int_ptr << ' ';
    }
  };
  std::for_each(src_array.begin(), src_array.end(), print_unique_int_ptr);
  std::cout << "] to [";
  std::array<std::unique_ptr<int>, src_array.size() * 2> dst_array{};
  std::move(src_array.begin(), src_array.end(), dst_array.begin());
  std::for_each(dst_array.begin(), dst_array.end(), print_unique_int_ptr);
  std::cout << "], src is now [";
  std::for_each(src_array.begin(), src_array.end(), print_unique_int_ptr);
  std::cout << "]\n";
  return 0;
}
