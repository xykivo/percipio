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

/// C++ count main entry point
int main() {
  std::cout << "STL std::copy samples\n";
  static constexpr std::array<int, 8> kSrcArray{0, 1, 2, 3, 4, 5, 6, 7};
  std::cout << "Copied [";
  xykivo::percipio::util::OutputRange(std::cout, kSrcArray.begin(),
                                      kSrcArray.end(), " ");
  std::array<int, 8> dst_array{};
  std::copy(kSrcArray.begin(), kSrcArray.end(), dst_array.begin());
  std::cout << "] to [";
  xykivo::percipio::util::OutputRange(std::cout, dst_array.begin(),
                                      dst_array.end(), " ");
  std::cout << "]\n";
  return 0;
}
