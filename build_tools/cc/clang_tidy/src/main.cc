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

#include <fstream>
#include <iostream>
#include <vector>

#include "xykivo/ccbuildutils/argument_parser.h"
#include "xykivo/ccbuildutils/process.h"

namespace {

int RunClangTidy(std::string_view path_list, std::string_view copts) {
  std::string command_line{"clang-tidy --header-filter=.* "};
  command_line.append(path_list);
  command_line.append(" -- -x c++ ");
  command_line.append(copts);
  std::replace(command_line.begin(), command_line.end(), ',', ' ');
  xykivo::ccbuildutils::Process clang_tidy(command_line);
  std::string clang_tidy_output{};
  static constexpr int kOutputSize{128};
  std::optional<std::string> clang_tidy_pipe_output =
      clang_tidy.Read(kOutputSize);
  while (clang_tidy_pipe_output) {
    clang_tidy_output.append(clang_tidy_pipe_output.value());
    clang_tidy_pipe_output = clang_tidy.Read(kOutputSize);
  }
  std::cout << clang_tidy_output << std::endl;
  return clang_tidy.Close();
}

}  // namespace

int main(int argc, const char* argv[]) {
  std::vector<xykivo::ccbuildutils::CommandLineArgument> arguments{
      xykivo::ccbuildutils::CommandLineArgument{"lint_succeeded"},
      xykivo::ccbuildutils::CommandLineArgument{"src_files"}};
  std::vector<xykivo::ccbuildutils::CommandLineOption> options{
      xykivo::ccbuildutils::CommandLineOption{"--copts", ""}};
  parse_args(argc, argv, arguments, options);
  int result = RunClangTidy(arguments[1].GetValue<std::string>(),
                            options[0].GetValue<std::string>());

  std::cout << "clang-tidy result=" << result << std::endl;

  if (0 == result) {
    std::ofstream out{arguments[0].GetValue<std::string>(),
                      /* mode */ std::ios_base::out};
    out << "C++ lint of " << arguments[1].GetValue<std::string>()
        << " succeeded";
  }
  return result;
}