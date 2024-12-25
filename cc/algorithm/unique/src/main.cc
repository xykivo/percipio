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

#include <cstddef>

#include <algorithm>
#include <array>
#include <iostream>

int main() {
  std::cout << "STL std::unique example\n";
  static constexpr size_t kArraySize{16};
  std::array<int, kArraySize> array{
      0, 1, 2, 2, 3, 3, 3, 4,   // NOLINT(readability-magic-numbers)
      4, 4, 4, 5, 5, 5, 5, 5};  // NOLINT(readability-magic-numbers)
  std::cout << "Equality unique - array=[";
  auto print_int = [](int integer) { std::cout << integer << ' '; };
  // NOLINTNEXTLINE(modernize-use-ranges)
  std::for_each(array.begin(), array.end(), print_int);
  // NOLINTNEXTLINE(modernize-use-ranges)
  auto* unique_array_end = std::unique(array.begin(), array.end());
  std::cout << "] -> array=[";
  // NOLINTNEXTLINE(modernize-use-ranges)
  std::for_each(array.begin(), unique_array_end, print_int);
  std::cout << "]\n";

  std::cout << "Predicate (equal LSB) unique - array=[";
  array = {0, 1, 3, 5, 7, 2, 4, 6,   // NOLINT(readability-magic-numbers)
           8, 1, 2, 3, 4, 5, 6, 7};  // NOLINT(readability-magic-numbers)

  // NOLINTNEXTLINE(modernize-use-ranges)
  std::for_each(array.begin(), array.end(), print_int);
  auto equal_lsb = [](int int_0, int int_1) {
    static constexpr int kLsbMask{0x1};
    return ((int_0 & kLsbMask) == (int_1 & kLsbMask));
  };
  // NOLINTNEXTLINE(modernize-use-ranges)
  unique_array_end = std::unique(array.begin(), array.end(), equal_lsb);
  std::cout << "] -> array=[";
  // NOLINTNEXTLINE(modernize-use-ranges)
  std::for_each(array.begin(), unique_array_end, print_int);
  std::cout << "]\n";

  return 0;
}
