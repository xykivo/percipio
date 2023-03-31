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
#include <vector>

#include "xykivo/percipio/util/out_stream.h"

namespace {

/// Simple function that uses std::count algorithm to count how many time an
/// integer appears in an array of integers
template <size_t ArraySize>
void CountInt(const std::array<int, ArraySize>& array, int integer) {
  std::cout << integer << " appears "
            << std::count(array.begin(), array.end(), integer) << " times in ";
  xykivo::percipio::util::OutputRange(std::cout, array.begin(), array.end(),
                                      " ");
  std::cout << '\n';
}

}  // namespace

/// C++ count main entry point
int main() {
  std::cout << "STL std::count samples\n";
  static constexpr std::array<int, 10> kIntegerArray{1, 2, 2, 3, 3,
                                                     3, 4, 4, 4, 4};
  static constexpr int kMaxIntCounted = 4;
  for (int i = 0; kMaxIntCounted > i; ++i) {
    CountInt(kIntegerArray, i);
  }
  return 0;
}
