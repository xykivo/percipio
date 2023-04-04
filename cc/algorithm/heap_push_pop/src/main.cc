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
#include <vector>

int main() {
  std::cout << "STL std::make_heap, std::heap_push and std::heap_pop example\n";
  std::vector<int> heap{17, 8, 19, -4, -6,  // NOLINT(readability-magic-numbers)
                        10, 2, 17, 21};     // NOLINT(readability-magic-numbers)
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
  std::make_heap(heap.begin(), heap.end());
  print_range(heap.begin(), heap.end());
  print_is_heap(heap.begin(), heap.end());
  std::cout << '\n';
  static constexpr std::array kArray{-7, 24, 14, 9};
  for (const auto value : kArray) {
    heap.push_back(value);
    std::push_heap(heap.begin(), heap.end());
    std::cout << "heap push " << value << " - ";
    print_range(heap.begin(), heap.end());
    std::cout << '\n';
  }
  for (size_t i = 0; kArray.size() > i; ++i) {
    std::pop_heap(heap.begin(), heap.end());
    heap.pop_back();
    std::cout << "heap pop - ";
    print_range(heap.begin(), heap.end());
    std::cout << '\n';
  }
  return 0;
}
