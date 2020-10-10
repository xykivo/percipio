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
  std::cout << "STL std::remove_copy sample\n";
  static constexpr int kArraySize{8};
  static constexpr std::array<int, kArraySize> kSrcArray{-1, 1, -1, 2,
                                                         -1, 3, -1, 4};
  std::array<int, kSrcArray.size()> dst_array{};
  static constexpr int kRemovedElement{-1};
  std::cout << "copy (except " << kRemovedElement << ") from [";
  auto print_int = [](int i) { std::cout << i << ' '; };
  std::for_each(kSrcArray.begin(), kSrcArray.end(), print_int);
  std::cout << "] to [";
  auto* iter = std::remove_copy(kSrcArray.begin(), kSrcArray.end(),
                                dst_array.begin(), kRemovedElement);
  std::for_each(dst_array.begin(), dst_array.end(), print_int);
  std::cout << "]\n";
  std::cout << "past the end iterator points to " << *iter << "\n";
}
