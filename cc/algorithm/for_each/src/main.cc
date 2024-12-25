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
#include <exception>
#include <iostream>
#include <vector>

#include "xykivo/percipio/util/out_stream.h"

namespace {

constexpr std::array<int, 8> kPositiveIntegers{1, 2, 3, 4, 5, 6, 7, 8};

/// Simple sampele of using for_each algorithm to negate a range of integers
template <size_t ArraySize>
void ForEachNegate(const std::array<int, ArraySize>& array) {
  std::vector<int> vec{};
  auto negate_into_vec = [&vec](int integer) { vec.push_back(-1 * integer); };
  std::for_each(array.begin(), array.end(), negate_into_vec);
  std::cout << "original array = ";
  xykivo::percipio::util::OutputRange(std::cout, array.begin(), array.end(),
                                      " ");
  std::cout << '\n';
  std::cout << "negated array values in vector = ";
  xykivo::percipio::util::OutputRange(std::cout, vec.begin(), vec.end(), " ");
  std::cout << '\n';
}

template <size_t ArraySize>
constexpr int Sum(const std::array<int, ArraySize>& array) {
  int sum = 0;
  auto add_to_sum = [&sum](int integer) { sum += integer; };
  std::for_each(array.begin(), array.end(), add_to_sum);
  return sum;
}

template <size_t ArraySize>
void ForEachSum(const std::array<int, ArraySize>& array) {
  std::cout << "The sum of ";
  xykivo::percipio::util::OutputRange(std::cout, array.begin(), array.end(),
                                      " ");
  std::cout << " = " << Sum(array) << '\n';
}

}  // namespace

/// C++ for_each main entry point
int main() {
  try {
    std::cout << "STL std::for_each samples\n";
    ForEachNegate(kPositiveIntegers);
    ForEachSum(kPositiveIntegers);
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
  return 0;
}
