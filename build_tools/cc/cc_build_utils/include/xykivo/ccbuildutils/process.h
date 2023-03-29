// BSD 3-Clause License
//
// Copyright (c) 2023, Dror Smolarsky
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

#pragma once

#include <cstdio>

#include <optional>
#include <string>
#include <string_view>

namespace xykivo {
namespace ccbuildutils {

/// Manager (sub) process life time and resources
///
/// The parent process can read the sub process (standard) output can be read.
/// The sub process launched does not accept input from the parent process.
/// The sub process launched runs until completion. Do NOT of launch a sub
/// process that will not terminate.
class Process {
 public:
  Process(const Process&) = delete;
  Process& operator=(const Process&) = delete;

  Process(std::string_view command);

  Process(Process&& other) noexcept;
  Process& operator=(Process&& other) noexcept;

  ~Process();

  /// Swap the content of this process with other
  ///
  /// \note This method name does not conform to the code style, since it must
  ///       conform to the STL naming, so it can be used in STL algorithms and
  ///       containers.
  void swap(Process& other)  ///< [inout] The process this is swapped with
      noexcept;

  /// Wait for the process to close
  ///
  /// This method will block until the process completes.
  /// \return The process exit status, 0 if the process is already closed.
  int Close() noexcept;

  /// Read characaters from the process standard output
  ///
  /// This method will read up to count characters from the process standard
  /// output.
  /// \return A string that contains the characters read the process standard
  ///         output. The string will be empty if no characters were read from
  ///         process standard output, if the process is already closed, or an
  ///         error occured.
  std::optional<std::string> Read(int count) noexcept;

 private:
  FILE* pipe_{NULL};
};

// template <typename Callback, size_t PipeBufferSize>
// int execute(std::string_view command, Callback readPipeCallback) {
//   std::array<std::uint8_t, PipeBufferSize> pipe_buffer{};
// }

}  // namespace ccbuildutils
}  // namespace xykivo