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
#include <array>
#include <iostream>
#include <memory>

#include "xykivo/percipio/util/out_stream.h"

namespace {

class IntPtr {
 public:
  IntPtr(const IntPtr& other) = delete;
  IntPtr& operator=(const IntPtr& other) = delete;

  IntPtr() noexcept = default;
  explicit IntPtr(int i) : i_(std::make_unique<int>(i)) {}
  IntPtr(IntPtr&& other) noexcept = default;
  IntPtr& operator=(IntPtr&& other) noexcept = default;

  void swap(IntPtr& other) { std::swap(i_, other.i_); }

  friend std::ostream& operator<<(std::ostream& out, const IntPtr& int_ptr) {
    if (nullptr == int_ptr.i_) {
      out << "nullptr";
    } else {
      out << *int_ptr.i_;
    }
    return out;
  }

 private:
  std::unique_ptr<int> i_;
};

}  // namespace

/// C++ move main entry point
int main() {
  std::cout << "STL std::move samples\n";
  static constexpr size_t kArraySize{4};
  std::array<IntPtr, kArraySize> src_array{IntPtr(0), IntPtr(1), IntPtr(2),
                                           IntPtr(3)};
  std::cout << "Moved [";
  xykivo::percipio::util::OutputRange(std::cout, src_array.begin(),
                                      src_array.end(), " ");
  std::cout << "] to [";
  std::array<IntPtr, src_array.size() * 2> dst_array{};
  std::move(src_array.begin(), src_array.end(), dst_array.begin());
  xykivo::percipio::util::OutputRange(std::cout, dst_array.begin(),
                                      dst_array.end(), " ");
  std::cout << "], src is now [";
  xykivo::percipio::util::OutputRange(std::cout, src_array.begin(),
                                      src_array.end(), " ");
  std::cout << "]\n";
  return 0;
}
