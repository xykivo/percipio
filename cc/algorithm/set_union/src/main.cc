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
  std::cout << "STL std::union example\n";
  std::array src_0{
      -7, -6, -5, -4, -3, -2, -1,      // NOLINT(readability-magic-numbers)
      1,  2,  3,  4,  5,  6,  7,  8};  // NOLINT(readability-magic-numbers)
  std::array src_1{
      9, 10, 11, 12, 13, 14, 15,      // NOLINT(readability-magic-numbers)
      1, 2,  3,  4,  5,  6,  7,  8};  // NOLINT(readability-magic-numbers)
  auto print_range = [](auto begin, auto end) {
    std::cout << "[";
    auto print_value = [](auto val) { std::cout << val << ' '; };
    std::for_each(begin, end, print_value);
    std::cout << "]";
  };
  std::cout << '\n';
  std::sort(src_0.begin(), src_0.end());
  std::sort(src_1.begin(), src_1.end());
  std::cout << "the union between ";
  print_range(src_0.begin(), src_0.end());
  std::cout << " and ";
  print_range(src_1.begin(), src_1.end());
  std::cout << " is ";
  std::array<int, src_0.size() + src_1.size()> dst{};
  std::set_union(src_0.begin(), src_0.end(), src_1.begin(), src_1.end(),
                 dst.begin());
  print_range(dst.begin(), dst.end());
  std::cout << '\n';
  return 0;
}
