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

#include <cstdlib>

#include <algorithm>
#include <fstream>
#include <optional>
#include <regex>
#include <stdexcept>
#include <vector>

#include "xykivo/ccbuildutils/argument_parser.h"
#include "xykivo/ccbuildutils/process.h"

namespace {

std::string RunClangFormat(std::string_view path_list) {
  std::string command_line =
      "clang-format --color --output-replacements-xml --style=file ";
  command_line.append(path_list);
  std::replace(command_line.begin(), command_line.end(), ',', ' ');
  xykivo::ccbuildutils::Process clang_format(command_line);
  std::string clang_format_output{};
  static constexpr int kOutputSize{128};
  std::optional<std::string> clang_format_pipe_output =
      clang_format.Read(kOutputSize);
  while (clang_format_pipe_output) {
    clang_format_output.append(clang_format_pipe_output.value());
    clang_format_pipe_output = clang_format.Read(kOutputSize);
  }
  clang_format.Close();
  return clang_format_output;
}

bool CheckForStyleErrors(std::string_view clang_format_output) {
  static const std::regex kReplacementRegex{"replacement offset="};
  std::cmatch replacement_match;
  if (std::regex_search(clang_format_output.begin(), clang_format_output.end(),
                        replacement_match, kReplacementRegex)) {
    return true;
  }
  return false;
}

}  // namespace

int main(int argc, const char* argv[]) {
  std::vector<xykivo::ccbuildutils::CommandLineArgument> arguments{
      xykivo::ccbuildutils::CommandLineArgument{"code_style_check_succeeded"},
      xykivo::ccbuildutils::CommandLineArgument{"src_files"}};
  std::vector<xykivo::ccbuildutils::CommandLineOption> options{};
  parse_args(argc, argv, arguments, options);
  std::string clang_format_output =
      RunClangFormat(arguments[1].GetValue<std::string>());
  if (CheckForStyleErrors(clang_format_output)) {
    return 1;
  }
  std::ofstream out{arguments[0].GetValue<std::string>(),
                    /* mode */ std::ios_base::out};
  out << "C++ code style check of " << arguments[1].GetValue<std::string>()
      << " succeeded";
  return 0;
}
