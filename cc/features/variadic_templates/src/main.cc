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

#include <iostream>
#include <string_view>

namespace {

template <typename T>
void PrintArgs(const T& t) {
  std::cout << " " << t;
}

template <typename T, typename... Args>
void PrintArgs(const T& t, const Args&... args) {
  std::cout << " " << t;
  PrintArgs(args...);
}

}  // namespace

int main() {
  std::cout
      << "Variadic template sample - compile time recursive print arguments\n";
  static constexpr int kInt0{0};
  static constexpr int kInt1{1};
  static constexpr std::string_view kString0{"string-0"};
  static constexpr std::string_view kString1{"string-1"};
  PrintArgs(kInt0, kString0, kInt1, kString1);
  std::cout << "\n\n";
}
