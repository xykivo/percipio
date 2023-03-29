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

#include "xykivo/ccbuildutils/process.h"

#include <cstdio>

#include <stdexcept>

#include <optional>
#include <string>
#include <string_view>

namespace xykivo {
namespace ccbuildutils {

namespace {

FILE* OpenProcess(std::string_view command) {
  FILE* process = popen(command.data(), "r");
  if (NULL == process) {
    throw std::runtime_error("Failed to open process");
  }
  return process;
}

}  // namespace

Process::Process(std::string_view command) : pipe_(OpenProcess(command)) {}

Process::Process(Process&& other) noexcept { swap(other); }

Process& Process::operator=(Process&& other) noexcept {
  swap(other);
  return (*this);
}

Process::~Process() { Close(); }

void Process::swap(Process& other) noexcept { std::swap(pipe_, other.pipe_); }

int Process::Close() noexcept {
  int result{0};
  if (NULL != pipe_) {
    result = pclose(pipe_);
    pipe_ = NULL;
  }
  return result;
}

std::optional<std::string> Process::Read(int count) noexcept {
  if (NULL == pipe_) {
    return {};
  }
  std::string output(count, '\0');
  if (nullptr == fgets(&(output[0]), count, pipe_)) {
    return {};
  }
  return output;
}

}  // namespace ccbuildutils
}  // namespace xykivo
