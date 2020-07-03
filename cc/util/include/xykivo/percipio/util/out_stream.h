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

#ifndef XYKIVO_PERCIPIO_UTIL_OUT_STREAM_H_
#define XYKIVO_PERCIPIO_UTIL_OUT_STREAM_H_

#include <algorithm>
#include <iterator>
#include <ostream>
#include <string_view>

namespace xykivo {
namespace percipio {
namespace util {

/// Output an iterator range to an output stream with the given delimiter
template <typename OutputIter>
void OutputRange(std::ostream& out, OutputIter begin, OutputIter end,
                 std::string_view delimiter) {
  std::copy(begin, end,
            std::ostream_iterator<typename OutputIter::value_type>(
                out, delimiter.data()));
}

/// Output a pointer range to an output stream with the given delimiter
template <typename T>
void OutputRange(std::ostream& out, T* begin, T* end,
                 std::string_view delimiter) {
  std::copy(begin, end, std::ostream_iterator<T>(out, delimiter.data()));
}

}  // namespace util
}  // namespace percipio
}  // namespace xykivo

#endif  // XYKIVO_PERCIPIO_UTIL_OUT_STREAM_H_
