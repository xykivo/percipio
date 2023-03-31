// BSD 3-Clause License
//
// Copyright (c) 2020-2021, Dror Smolarsky
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
  std::cout << "STL std::partial_sort_copy example\n";
  static constexpr size_t kArraySize{15};
  static constexpr std::array<int, kArraySize> kSrcArray{
      1,  -1, 2,  -2, 3,  -3, 4, 0,  // NOLINT(readability-magic-numbers)
      -4, 5,  -5, 6,  -6, 7,  -7};   // NOLINT(readability-magic-numbers)
  auto print_range = [](const auto begin, const auto end) {
    std::cout << "array=[";
    auto print_int = [](int i) { std::cout << i << ' '; };
    std::for_each(begin, end, print_int);
    std::cout << "]\n";
  };
  print_range(kSrcArray.begin(), kSrcArray.end());
  std::array<int, kSrcArray.size() / 2> dst_array{};
  std::partial_sort_copy(kSrcArray.begin(), kSrcArray.end(), dst_array.begin(),
                         dst_array.end());
  print_range(dst_array.begin(), dst_array.end());
  return 0;
}
