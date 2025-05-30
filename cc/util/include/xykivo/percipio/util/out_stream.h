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
                out,
                // TODO(xykivo@gmail.com) There is no way to pass a safe string
                //    using char* to std::ostream_iterator constructor
                // NOLINTNEXTLINE(bugprone-suspicious-stringview-data-usage)
                delimiter.data()));
}

/// Output a pointer range to an output stream with the given delimiter
template <typename T>
void OutputRange(std::ostream& out, T* begin, T* end,
                 std::string_view delimiter) {
  std::copy(begin, end,
            std::ostream_iterator<T>(
                out,
                // TODO(xykivo@gmail.com) There is no way to pass a safe string
                //    using char* to std::ostream_iterator constructor
                // NOLINTNEXTLINE(bugprone-suspicious-stringview-data-usage)
                delimiter.data()));
}

}  // namespace util
}  // namespace percipio
}  // namespace xykivo

#endif  // XYKIVO_PERCIPIO_UTIL_OUT_STREAM_H_
