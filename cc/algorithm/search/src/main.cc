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
#include <functional>
#include <iostream>
#include <string_view>

namespace {

/// Simple funciton that finds the first occurence of a sub string in a string
/// using the C++ std::search algorithm
void FindSubString(const std::string_view str, const std::string_view sub_str) {
  if (str.end() ==
      // NOLINTNEXTLINE(modernize-use-ranges)
      std::search(str.begin(), str.end(), sub_str.begin(), sub_str.end())) {
    std::cout << sub_str << " not found in " << str << '\n';
  } else {
    std::cout << sub_str << " found in " << str << '\n';
  }
}

template <typename Searcher>
void SearchString(const std::string_view str, const std::string_view sub_str) {
  // NOLINTNEXTLINE(modernize-use-ranges)
  if (str.end() == std::search(str.begin(), str.end(),
                               Searcher(sub_str.begin(), sub_str.end()))) {
    std::cout << sub_str << " not found in " << str << '\n';
  } else {
    std::cout << sub_str << " found in " << str << '\n';
  }
}

}  // namespace

/// C++ std::search sample main entry point
int main() {
  std::cout << "STL simple std::search samples\n";
  static constexpr std::string_view kString{"hello world"};
  static constexpr std::string_view kSubString0{"world"};
  FindSubString(kString, kSubString0);
  static constexpr std::string_view kSubString1{"universe"};
  FindSubString(kString, kSubString1);

  std::cout << "\nSTL std::search with std::default_searcher sample\n";
  SearchString<std::default_searcher<std::string_view::iterator>>(kString,
                                                                  kSubString0);
  SearchString<std::default_searcher<std::string_view::iterator>>(kString,
                                                                  kSubString1);

  // Commented out, since it's not supported on all compiler versions in *nix
  // systems std::cout << "\nSTL std::search with std::boyer_moore_searcher
  // sample\n";
  // SearchString<std::boyer_moore_searcher<std::string_view::iterator>>(
  //     kString, kSubString0);
  // SearchString<std::boyer_moore_searcher<std::string_view::iterator>>(
  //     kString, kSubString1);

  // std::cout
  //     << "\nSTL std::search with std::boyer_moore_horspool_searcher
  //     sample\n";
  // SearchString<std::boyer_moore_horspool_searcher<std::string_view::iterator>>(
  //     kString, kSubString0);
  // SearchString<std::boyer_moore_horspool_searcher<std::string_view::iterator>>(
  //     kString, kSubString1);

  return 0;
}
