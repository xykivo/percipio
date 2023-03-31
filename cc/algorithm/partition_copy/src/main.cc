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
  std::cout << "STL std::partition_copy and std::is_partitioned example\n";
  static constexpr size_t kArraySize{15};
  std::array<int, kArraySize> array{
      0,  1, -1, 2, -2, 3, -3, 4,  // NOLINT(readability-magic-numbers)
      -4, 5, -5, 6, -6, 7, -7};    // NOLINT(readability-magic-numbers)
  auto is_greater_than_pivot = [](int i) {
    static constexpr int kPivot{0};
    return i > kPivot;
  };
  auto print_is_array_partitioned =
      [is_greater_than_pivot](const std::array<int, kArraySize>& array) {
        std::cout << "array=[";
        auto print_int = [](int i) { std::cout << i << ' '; };
        std::for_each(array.begin(), array.end(), print_int);
        std::cout << "] is ";
        std::cout << (std::is_partitioned(array.begin(), array.end(),
                                          is_greater_than_pivot)
                          ? ""
                          : "not");
        std::cout << " partitoned\n";
      };
  print_is_array_partitioned(array);
  std::array<int, kArraySize> greater_than_pivot_array{};
  std::array<int, kArraySize> less_than_pivot_array{};
  std::partition_copy(array.begin(), array.end(),
                      greater_than_pivot_array.begin(),
                      less_than_pivot_array.begin(), is_greater_than_pivot);
  auto print_array = [](const std::array<int, kArraySize>& array) {
    std::cout << "array=[";
    auto print_int = [](int i) { std::cout << i << ' '; };
    std::for_each(array.begin(), array.end(), print_int);
    std::cout << "]";
  };
  std::cout << "greater than pivot ";
  print_array(greater_than_pivot_array);
  std::cout << '\n';
  std::cout << "less than pivot ";
  print_array(less_than_pivot_array);
  std::cout << '\n';
  return 0;
}