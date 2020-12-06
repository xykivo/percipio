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
#include <iostream>

/// C++ swap sample main entry point
int main() {
  std::cout << "STL std::swap samples\n";
  int i0{0};
  int i1{1};
  std::cout << "swapping i0=" << i0 << " with i1=" << i1 << " -> ";
  std::swap(i0, i1);
  std::cout << "i0=" << i0 << " i1=" << i1 << '\n';
  return 0;
}
