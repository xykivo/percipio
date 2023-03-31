// BSD 3-Clause License
//
// Copyright (c) 2021, Dror Smolarsky
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

#include <cmath>

#include <algorithm>
#include <array>
#include <iostream>

namespace {

bool AbsLessThan(int lhs, int rhs) { return (std::abs(lhs) < std::abs(rhs)); }

}  // namespace

int main() {
  std::cout << "STL std::stable_sort example\n";
  static constexpr size_t kArraySize{15};
  std::array<int, kArraySize> array{
      0,  4, -4, 7, -7, 5, -5, 1,  // NOLINT(readability-magic-numbers)
      -1, 3, -3, 6, -6, 2, -2};    // NOLINT(readability-magic-numbers)
  auto print_array = [](std::array<int, kArraySize>& array) {
    std::cout << "array=[";
    auto print_int = [](int i) { std::cout << i << ' '; };
    std::for_each(array.begin(), array.end(), print_int);
    std::cout << "] ";
    std::cout << (std::is_sorted(array.begin(), array.end(), AbsLessThan)
                      ? ""
                      : "not");
    std::cout << " sorted\n";
  };
  print_array(array);
  std::stable_sort(array.begin(), array.end(), AbsLessThan);
  print_array(array);
  return 0;
}