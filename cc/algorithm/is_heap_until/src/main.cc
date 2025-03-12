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

#include <cstdint>

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  try {
    std::cout << "STL std::make_heap and std::is_heap_until example\n";
    std::vector<int> heap{
        17, 8,  19, -4, -6,  // NOLINT(readability-magic-numbers)
        10, 2,  17, 21,      // NOLINT(readability-magic-numbers)
        7,  -7, 6,  9,  13,  // NOLINT(readability-magic-numbers)
        33, 25, 16};         // NOLINT(readability-magic-numbers)
    auto print_range = [](auto begin, auto end) {
      std::cout << "[";
      auto print_value = [](auto val) { std::cout << val << ' '; };
      std::for_each(begin, end, print_value);
      std::cout << "]";
    };
    auto print_is_heap = [](auto begin_range, auto end_range) {
      if (std::is_heap(begin_range, end_range)) {
        std::cout << " is a heap";
      } else {
        std::cout << " is not a heap";
      }
    };
    print_range(heap.begin(), heap.end());
    print_is_heap(heap.begin(), heap.end());
    std::cout << '\n';
    std::make_heap(heap.begin(),
                   heap.begin() + static_cast<int64_t>(heap.size() / 2));
    print_range(heap.begin(), heap.end());
    print_is_heap(heap.begin(), heap.end());
    std::cout << '\n';
    // NOLINTNEXTLINE(modernize-use-ranges)
    const auto heap_end = std::is_heap_until(heap.begin(), heap.end());
    print_range(heap.begin(), heap_end);
    print_is_heap(heap.begin(), heap_end);
    std::cout << '\n';
  } catch (...) {
    return 1;
  }
  return 0;
}
