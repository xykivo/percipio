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
  std::cout << "STL std::replace_copy sample\n";
  static constexpr int kArraySize{8};
  std::array<int, kArraySize> src_array{-1, 1, -1, 2, -1, 3, -1, 4};
  static constexpr int kReplaced{-1};
  std::cout << "replace " << kReplaced << " in [";
  auto print_int = [](int integer) { std::cout << integer << ' '; };
  // NOLINTNEXTLINE(modernize-use-ranges)
  std::for_each(src_array.begin(), src_array.end(), print_int);
  static constexpr int kReplacement{0};
  std::cout << "] with " << kReplacement << " copied to [";
  std::array<int, kArraySize> dst_array{};
  std::replace_copy(src_array.begin(), src_array.end(), dst_array.begin(),
                    kReplaced, kReplacement);
  // NOLINTNEXTLINE(modernize-use-ranges)
  std::for_each(dst_array.begin(), dst_array.end(), print_int);
  std::cout << "]\n";
}
