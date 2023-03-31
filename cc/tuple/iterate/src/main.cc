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
#include <string>
#include <tuple>
#include <utility>

namespace {

template <typename... Types, size_t... indices>
void PrintTupleElements(const std::tuple<Types...>& tpl,
                        std::integer_sequence<size_t, indices...>) {
  ((std::cout << std::get<indices>(tpl) << ' '), ...);
}

template <typename... Types>
void PrintTupleElements(const std::tuple<Types...>& tpl) {
  std::index_sequence_for<Types...> index_sequence;
  PrintTupleElements(tpl, index_sequence);
  std::cout << '\n';
}

}  // namespace

int main() {
  std::cout << "Simple sample of iterating over tuple values\n";
  auto tpl = std::make_tuple<bool, float, int, std::string>(false, 0.1F, 1,
                                                            "some string");
  PrintTupleElements(tpl);
  return 0;
}
