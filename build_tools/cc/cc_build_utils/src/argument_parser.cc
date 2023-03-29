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

#include "xykivo/ccbuildutils/argument_parser.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <regex>
#include <span>
#include <stdexcept>
#include <string_view>

namespace xykivo {
namespace ccbuildutils {

template <>
std::string StringTo<std::string>(std::string_view str) {
  return std::string(str);
};

CommandLineArgument::CommandLineArgument(std::string_view name)
    : name_(name), value_("") {}

std::string CommandLineArgument::GetName() const { return name_; }

void CommandLineArgument::SetValue(std::string_view value) { value_ = value; }

CommandLineOption::CommandLineOption(std::string_view long_option,
                                     std::string_view default_value)
    : CommandLineOption(long_option, /* short_option */ "", default_value) {}

CommandLineOption::CommandLineOption(std::string_view long_option,
                                     std::string_view short_option,
                                     std::string_view default_value)
    : long_option_(long_option),
      short_option_(short_option),
      value_(default_value) {
  static const std::regex kLongOptionRegex{"\\-\\-[0-9a-zA-Z\\-]+"};
  std::smatch option_match;
  if (!std::regex_match(long_option_, option_match, kLongOptionRegex)) {
    throw std::invalid_argument(
        "Long command line argument must starts with '--' and contain at least "
        "one letter or digit");
  }
  if ("" != short_option_) {
    static const std::regex kShortOptionRegex{"\\-[0-9a-zA-Z\\-]w"};
    if (!std::regex_match(short_option_, option_match, kShortOptionRegex)) {
      throw std::invalid_argument(
          "Short command line argument must starts with '-' and exactly one "
          "letter or digit");
    }
  }
}

std::string CommandLineOption::GetLongOption() const { return long_option_; }

std::string CommandLineOption::GetShortOption() const { return short_option_; }

void CommandLineOption::SetValue(std::string_view value) { value_ = value; }

void parse_args(int argc, const char* argv[],
                std::span<CommandLineArgument> arguments,
                std::span<CommandLineOption> options) {
  if ((0 == argc) || (nullptr == argv)) {
    throw std::invalid_argument("Invalid command line arguments list");
  }
  size_t arg_index{0};
  for (int i = 1; i < argc; ++i) {
    const char* arg = argv[i];
    if ('-' == arg[0]) {
      auto option = std::find_if(options.begin(), options.end(),
                                 [arg](const CommandLineOption& opt) {
                                   return ((opt.GetLongOption() == arg) ||
                                           (opt.GetShortOption(), arg));
                                 });
      ++i;
      if (i == argc) {
        throw std::runtime_error("Missing option value");
      }
      option->SetValue(argv[i]);
    } else {
      if (arg_index >= arguments.size()) {
        throw std::runtime_error("Positional argument index out of range");
      }
      arguments[arg_index].SetValue(arg);
      ++arg_index;
    }
  }
  if (arg_index != arguments.size()) {
    throw std::runtime_error("Missing position arguments");
  }
}

}  // namespace ccbuildutils
}  // namespace xykivo
