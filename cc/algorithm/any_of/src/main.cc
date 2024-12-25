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

#include "xykivo/percipio/util/out_stream.h"

namespace {

constexpr std::array<int, 8> kPositiveIntegers{1, 2, 3, 4, 5, 6, 7, 8};

constexpr std::array<int, 8> kPositiveAndNegativeIntegers{-1, 1, -2, 2,
                                                          -3, 3, -4, 4};

constexpr std::array<int, 8> kNegativeIntegers{-1, -2, -3, -4, -5, -6, -7, -8};

template <size_t ArraySize>
void SimpleAnyOf(const std::array<int, ArraySize>& array) {
  auto is_positive = [](int integer) { return (0 < integer); };
  if (std::any_of(array.begin(), array.end(), is_positive)) {
    std::cout << "At least one of the integers in [";
    xykivo::percipio::util::OutputRange(std::cout, array.begin(), array.end(),
                                        " ");
    std::cout << "] is positive\n";
  } else {
    std::cout << "None of the integers in ";
    xykivo::percipio::util::OutputRange(std::cout, array.begin(), array.end(),
                                        " ");
    std::cout << " is positive\n";
  }
}

}  // namespace

/// C++ all_of main entry point
int main() {
  std::cout << "STL std::any_of samples\n";
  SimpleAnyOf(kPositiveIntegers);
  SimpleAnyOf(kPositiveAndNegativeIntegers);
  SimpleAnyOf(kNegativeIntegers);
  return 0;
}
