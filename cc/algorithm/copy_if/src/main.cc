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

#include "xykivo/percipio/util/out_stream.h"

/// C++ copy_if main entry point
int main() {
  std::cout << "STL std::copy_if samples\n";
  static constexpr size_t kArraySize{8};
  static constexpr std::array<int, kArraySize> kSrcArray{0, -1, 2, -3,
                                                         4, -5, 6, -7};
  std::cout << "Copied negative numbers from [";
  xykivo::percipio::util::OutputRange(std::cout, kSrcArray.begin(),
                                      kSrcArray.end(), " ");
  std::array<int, kSrcArray.size()> dst_array{};
  auto is_negative = [](int i) { return (0 > i); };
  std::copy_if(kSrcArray.begin(), kSrcArray.end(), dst_array.begin(),
               is_negative);
  std::cout << "] to [";
  xykivo::percipio::util::OutputRange(std::cout, dst_array.begin(),
                                      dst_array.end(), " ");
  std::cout << "]\n";
  return 0;
}
