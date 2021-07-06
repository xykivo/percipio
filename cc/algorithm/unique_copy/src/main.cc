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
  std::cout << "STL std::unique_copy example\n";
  static constexpr size_t kArraySize{16};
  std::array<int, kArraySize> src_array{
      0, 1, 2, 2, 3, 3, 3, 4,   // NOLINT(readability-magic-numbers)
      4, 4, 4, 5, 5, 5, 5, 5};  // NOLINT(readability-magic-numbers)
  std::cout << "Equality unique - array=[";
  auto print_int = [](int i) { std::cout << i << ' '; };
  std::for_each(src_array.begin(), src_array.end(), print_int);
  std::array<int, kArraySize> dst_array{};
  auto* unique_array_end =
      std::unique_copy(src_array.begin(), src_array.end(), dst_array.begin());
  std::cout << "] -> array=[";
  std::for_each(dst_array.begin(), unique_array_end, print_int);
  std::cout << "]\n";

  std::cout << "Predicate (equal LSB) unique - array=[";
  src_array = {0, 1, 3, 5, 7, 2, 4, 6,   // NOLINT(readability-magic-numbers)
               8, 1, 2, 3, 4, 5, 6, 7};  // NOLINT(readability-magic-numbers)
  // dst_array = {};
  std::for_each(src_array.begin(), src_array.end(), print_int);
  auto equal_lsb = [](int i0, int i1) {
    static constexpr int kLsbMask{0x1};
    return ((i0 & kLsbMask) == (i1 & kLsbMask));
  };
  unique_array_end = std::unique_copy(src_array.begin(), src_array.end(),
                                      dst_array.begin(), equal_lsb);
  std::cout << "] -> array=[";
  std::for_each(dst_array.begin(), unique_array_end, print_int);
  std::cout << "]\n";

  return 0;
}
