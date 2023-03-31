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

/// Simple function that uses std::mistmatch algorithm to compare 2 integer
/// array, and find the 1st mismatching integer.
template <size_t ArraySize>
void CompareRangeMismatch(const std::array<int, ArraySize>& array_0,
                          const std::array<int, ArraySize>& array_1) {
  std::cout << "comparing\n\t";
  xykivo::percipio::util::OutputRange(std::cout, array_0.begin(), array_0.end(),
                                      " ");
  std::cout << "\n\t";
  xykivo::percipio::util::OutputRange(std::cout, array_1.begin(), array_1.end(),
                                      " ");
  std::cout << '\n';
  auto not_equal = std::mismatch(array_0.begin(), array_0.end(),
                                 array_1.begin(), array_1.end());
  if (not_equal.first == array_0.end()) {
    std::cout << "\tall elements are equal\n";
  } else {
    std::cout << '\t' << *(not_equal.first) << " != " << *(not_equal.second)
              << '\n';
  }
  std::cout << '\n';
}

/// Simple function that uses std::mistmatch algorithm to find the first pair
/// of elements from 2 arrays, where at least one of the elements is less than
/// 0.
template <size_t ArraySize>
void IsLessThan0RangeMismatch(const std::array<int, ArraySize>& array_0,
                              const std::array<int, ArraySize>& array_1) {
  std::cout << "comparing\n\t";
  xykivo::percipio::util::OutputRange(std::cout, array_0.begin(), array_0.end(),
                                      " ");
  std::cout << "\n\t";
  xykivo::percipio::util::OutputRange(std::cout, array_1.begin(), array_1.end(),
                                      " ");
  std::cout << '\n';
  // The predicate returns true if there is no mismtach, and false if there is
  // a mismatch
  auto less_than_0_predicate = [](int int_0, int int_1) {
    return ((0 <= int_0) && (0 <= int_1));
  };
  auto is_less_than_0 =
      std::mismatch(array_0.begin(), array_0.end(), array_1.begin(),
                    array_1.end(), less_than_0_predicate);
  if (is_less_than_0.first == array_0.end()) {
    std::cout << "\tall elements greater than 0\n";
  } else {
    std::cout << '\t' << *(is_less_than_0.first) << " is less than 0,  or "
              << *(is_less_than_0.second) << " is less than 0\n";
  }
  std::cout << '\n';
}

}  // namespace

/// C++ mismatch main entry point
int main() {
  std::cout << "STL std::mismatch samples\n";
  static constexpr std::array<int, 8> kIntegerArray0{0, 1, 2, 3, 4, 5, 6, 7};
  static constexpr std::array<int, 8> kIntegerArray1{0, 1, 2, 3, 14, -5, 6, 7};
  CompareRangeMismatch(kIntegerArray0, kIntegerArray1);
  CompareRangeMismatch(kIntegerArray0, kIntegerArray0);
  IsLessThan0RangeMismatch(kIntegerArray0, kIntegerArray1);
  static constexpr std::array<int, 8> kIntegerArray2{0, 1, 2, 3, 14, 15, 6, 7};
  IsLessThan0RangeMismatch(kIntegerArray0, kIntegerArray2);
  return 0;
}
