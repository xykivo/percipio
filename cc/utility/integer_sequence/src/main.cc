// BSD 3-Clause License
//
// Copyright (c) 2021, Dror Smolarsky
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

#include <iostream>
#include <string_view>
#include <tuple>
#include <utility>

namespace {

template <typename T, T... Ints>
void PrintIntegerSequence(std::integer_sequence<T, Ints...> /* unused */) {
  ((std::cout << Ints << ' '), ...);
  std::cout << '\n';
}

}  // namespace

int main() {
  std::cout << "Simple sample of using std::integer_sequence\n";
  std::cout << "\nSequence\n";
  const std::integer_sequence<int, 9, -8, 7, -6, -5, 4, -3, 2, -1, 0>
      int_sequence;
  PrintIntegerSequence(int_sequence);
  std::cout << "\nInteger series\n";
  const std::make_integer_sequence<int, 9> int_series;
  PrintIntegerSequence(int_series);
  std::cout << "\nSize series\n";
  const std::make_integer_sequence<size_t, 7> size_series;
  PrintIntegerSequence(size_series);
  std::cout << "\nIndex series\n";
  const std::make_index_sequence<5> index_series;
  PrintIntegerSequence(index_series);
  return 0;
}
