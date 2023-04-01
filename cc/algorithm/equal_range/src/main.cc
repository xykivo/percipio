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
  std::cout << "STL std::equal_range example\n";
  static constexpr size_t kArraySize{15};
  std::array<int, kArraySize> array{
      -7, -6, -5, -4, -3, -2, 0, 0,  // NOLINT(readability-magic-numbers)
      0,  2,  3,  4,  5,  6,  7};    // NOLINT(readability-magic-numbers)
  auto print_range = [](auto begin, auto end) {
    std::cout << "range=[";
    auto print_value = [](auto integer) { std::cout << integer << ' '; };
    std::for_each(begin, end, print_value);
    std::cout << "]";
  };
  static constexpr int kZero{0};
  auto negative_range = std::equal_range(
      array.begin(), array.end(), kZero,
      [](const int& lhs, const int& rhs) { return (lhs < rhs); });
  std::cout << "Zeros in range ";
  print_range(array.begin(), array.end());
  std::cout << " = ";
  print_range(negative_range.first, negative_range.second);
  std::cout << '\n';
  return 0;
}
