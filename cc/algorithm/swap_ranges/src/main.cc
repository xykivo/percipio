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

/// C++ swap ranges main entry point
int main() {
  std::cout << "STL std::swap_ranges sample\n";
  static constexpr size_t kArraySize{8};
  // NOLINTNEXTLINE(readability-magic-numbers)
  std::array<int, kArraySize> array_0{0, 1, 2, 3, 4, 5, 6, 7};
  // NOLINTNEXTLINE(readability-magic-numbers)
  std::array<int, kArraySize> array_1{0, -1, -2, -3, -4, -5, -6, -7};
  std::cout << "swapping full range of array_0=[";
  auto print_int = [](int i) { std::cout << i << ' '; };
  std::for_each(array_0.begin(), array_0.end(), print_int);
  std::cout << "] with array_1=[";
  std::for_each(array_1.begin(), array_1.end(), print_int);
  std::cout << "] -> ";
  std::swap_ranges(array_0.begin(), array_0.end(), array_1.begin());
  std::cout << " array_0=[";
  std::for_each(array_0.begin(), array_0.end(), print_int);
  std::cout << "] array_1=";
  std::for_each(array_1.begin(), array_1.end(), print_int);
  std::cout << "]\n";
  return 0;
}
