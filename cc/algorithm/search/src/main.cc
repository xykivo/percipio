// Copyright (C) 2020 Dror Smolarsky
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include <algorithm>
#include <functional>
#include <iostream>
#include <string_view>

namespace {

/// Simple funciton that finds the first occurence of a sub string in a string
/// using the C++ std::search algorithm
void FindSubString(const std::string_view str, const std::string_view sub_str) {
  if (str.end() ==
      std::search(str.begin(), str.end(), sub_str.begin(), sub_str.end())) {
    std::cout << sub_str << " not found in " << str << '\n';
  } else {
    std::cout << sub_str << " found in " << str << '\n';
  }
}

template <typename Searcher>
void SearchString(const std::string_view str, const std::string_view sub_str) {
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

  std::cout << "\nSTL std::search with std::boyer_moore_searcher sample\n";
  SearchString<std::boyer_moore_searcher<std::string_view::iterator>>(
      kString, kSubString0);
  SearchString<std::boyer_moore_searcher<std::string_view::iterator>>(
      kString, kSubString1);

  std::cout
      << "\nSTL std::search with std::boyer_moore_horspool_searcher sample\n";
  SearchString<std::boyer_moore_horspool_searcher<std::string_view::iterator>>(
      kString, kSubString0);
  SearchString<std::boyer_moore_horspool_searcher<std::string_view::iterator>>(
      kString, kSubString1);

  return 0;
}
