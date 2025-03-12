// BSD 3-Clause License
//
// Copyright (c) 2022, Dror Smolarsky
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include <algorithm>
#include <array>
#include <iostream>

int main() {
  std::cout << "STL std::set_differrences example\n";
  std::array array{
      -7, -6, -5, -4, -3, -2, -1,      // NOLINT(readability-magic-numbers)
      1,  2,  3,  4,  5,  6,  7,  8,   // NOLINT(readability-magic-numbers)
      9,  10, 11, 12, 13, 14, 15,      // NOLINT(readability-magic-numbers)
      1,  2,  3,  4,  5,  6,  7,  8};  // NOLINT(readability-magic-numbers)
  auto print_range = [](auto begin, auto end) {
    std::cout << "[";
    auto print_value = [](auto val) { std::cout << val << ' '; };
    std::for_each(begin, end, print_value);
    std::cout << "]";
  };
  std::cout << '\n';
  std::sort(array.begin(), array.end());  // NOLINT(modernize-use-ranges)
  // NOLINTNEXTLINE(modernize-use-ranges)
  const auto* sub_array_begin = array.begin() + (array.size() / 2);
  // NOLINTNEXTLINE(modernize-use-ranges)
  const auto* sub_array_end = sub_array_begin + (array.size() / 4);
  std::cout << "the differrence between ";
  print_range(array.begin(), array.end());
  std::cout << " and ";
  print_range(sub_array_begin, sub_array_end);
  std::cout << " is ";
  std::array<int, array.size() * 3 / 4> difference{};
  // NOLINTNEXTLINE(modernize-use-ranges)
  std::set_difference(array.begin(), array.end(), sub_array_begin,
                      sub_array_end, difference.begin());
  print_range(difference.begin(), difference.end());
  std::cout << '\n';
  return 0;
}
