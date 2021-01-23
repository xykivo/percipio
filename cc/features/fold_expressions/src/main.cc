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

namespace {

template <typename... Ts>
void SimpleOutputPack(std::ostream& out, Ts const&... args) {
  out << "simple output pack - binary left fold: ";
  (out << ... << args);
  out << '\n';
}

template <typename... Ts>
void OutputPackInBrackets(std::ostream& out, Ts const&... args) {
  out << "simple output pack - binary right fold: ";
  size_t i{0};
  out << '[';
  ((out << args << (++i != sizeof...(Ts) ? ", " : "")), ..., (out << ']'));
  out << '\n';
}

template <typename... Ts>
void OutputPackLeftToRigth(std::ostream& out, Ts const&... args) {
  out << "output pack left to right - unary left fold: ";
  size_t i{0};
  (..., (out << args << (++i != sizeof...(Ts) ? ", " : "")));
  out << '\n';
}

template <typename... Ts>
void OutputPackRightToLeft(std::ostream& out, Ts const&... args) {
  out << "output pack right to left - unary right fold: ";
  size_t i{0};
  ((out << args << (++i != sizeof...(Ts) ? ", " : "")), ...);
  out << '\n';
}

}  // namespace

int main() {
  std::cout << "C++ fold expressions sample\n";
  SimpleOutputPack(std::cout, 0, 1, 2, 3);
  OutputPackInBrackets(std::cout, 0, 1, 2, 3);
  OutputPackLeftToRigth(std::cout, 0, 1, 2, 3);
  OutputPackRightToLeft(std::cout, 0, 1, 2, 3);
  return 0;
}
