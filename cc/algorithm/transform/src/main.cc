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
  std::cout << "STL std::transform samples\n";
  static constexpr std::array<int, 8> kInputArray{0, 1, 2, 3, 4, 5, 6, 7};
  std::cout << "transforming (unary increment by 1) [";
  auto print_int = [](int integer) { std::cout << integer << ' '; };
  // NOLINTNEXTLINE(modernize-use-ranges)
  std::for_each(kInputArray.begin(), kInputArray.end(), print_int);
  std::cout << "] to [";
  auto inc_by_1 = [](int integer) { return integer + 1; };
  std::array<int, kInputArray.size()> array{};
  // NOLINTNEXTLINE(modernize-use-ranges)
  std::transform(kInputArray.begin(), kInputArray.end(), array.begin(),
                 inc_by_1);
  // NOLINTNEXTLINE(modernize-use-ranges)
  std::for_each(array.begin(), array.end(), print_int);
  std::cout << "]\n";
  std::cout << "transforming (binary add) [";
  // NOLINTNEXTLINE(modernize-use-ranges)
  std::for_each(kInputArray.begin(), kInputArray.end(), print_int);
  std::cout << "] + [";
  // NOLINTNEXTLINE(modernize-use-ranges)
  std::for_each(array.begin(), array.end(), print_int);
  std::cout << "] = [";
  std::array<int, kInputArray.size()> sum{};
  auto add = [](int int_0, int int_1) { return int_0 + int_1; };
  // NOLINTNEXTLINE(modernize-use-ranges)
  std::transform(kInputArray.begin(), kInputArray.end(), array.begin(),
                 sum.begin(), add);
  // NOLINTNEXTLINE(modernize-use-ranges)
  std::for_each(sum.begin(), sum.end(), print_int);
  std::cout << "]\n";
  return 0;
}
