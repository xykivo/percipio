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

/// Simple function that finds the 1st integer in a given range of integers
/// that is greater than a given integer
template <size_t ArraySize>
void FindIntNotGreaterThanInRange(const std::array<int, ArraySize>& array,
                                  int integer) {
  auto greater_than = [&integer](int num) { return (num > integer); };
  auto greater_than_i =
      std::find_if_not(array.begin(), array.end(), greater_than);
  if (array.end() != greater_than_i) {
    std::cout << *greater_than_i << " is not greater than ";
  } else {
    std::cout << "No integer not greater than ";
  }
  std::cout << integer << " in [";
  xykivo::percipio::util::OutputRange(std::cout, array.begin(), array.end(),
                                      " ");
  std::cout << "]\n";
}

}  // namespace

/// C++ std::find_if_not sample main entry point
int main() {
  std::cout << "STL std::find_if_not samples\n";
  static constexpr std::array<int, 8> kIntegerArray{7, 6, 5, 4, 3, 2, 1, 0};
  static constexpr int kSmallInt = 5;
  FindIntNotGreaterThanInRange(kIntegerArray, kSmallInt);
  static constexpr int kLargeInt = -5;
  FindIntNotGreaterThanInRange(kIntegerArray, kLargeInt);
  return 0;
}
