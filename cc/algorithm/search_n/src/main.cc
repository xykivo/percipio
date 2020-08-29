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
#include <iostream>
#include <string_view>

/// C++ std::search_n sample main entry point
int main() {
  static constexpr char kOne{'1'};
  static constexpr std::string_view kBinaryString{"0110011001111000"};
  static constexpr int kMaxConsecutiveOnesSearched{
      static_cast<int>(kBinaryString.size())};
  for (int i = 1; kMaxConsecutiveOnesSearched > i; ++i) {
    if (kBinaryString.end() !=
        std ::search_n(kBinaryString.begin(), kBinaryString.end(), i, kOne)) {
      std::cout << "Found " << i << " consecutive 1's in " << kBinaryString
                << '\n';
    } else {
      std::cout << i << " consecutive 1's not found in " << kBinaryString
                << '\n';
    }
  }
  return 0;
}
