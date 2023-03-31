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

#include <span>
#include <string>
#include <string_view>

namespace xykivo {
namespace ccbuildutils {

/// Convert string to a give type
///
/// \return The value the string is converted to
template <typename T>
T StringTo(std::string_view str);  ///< [in] The string converted

/// Positional command line argument data container
///
/// Holds the argument name and value.
class CommandLineArgument {
 public:
  explicit CommandLineArgument(std::string_view name);

  /// Access the argument name (based on the long option)
  ///
  /// \return The argument name (derived from the long option)
  std::string GetName() const;

  /// Access the positional argument value as a given type
  ///
  /// \return The argument value as the given type
  template <typename T>
  T GetValue() const {
    return StringTo<T>(value_);
  }

  /// Set the positional argument value
  void SetValue(std::string_view value);  ///< [in] The argument value string

 private:
  std::string name_{};
  std::string value_{};
};

/// Optional command line argument data container
///
/// Holds the short option, long option and value of the argument.
/// Used to both the define the argument, and its default value, and return
/// the parsed value (as a string).
/// Only support a single optional value, which must be passed after the
/// option name in the command line.
class CommandLineOption {
 public:
  CommandLineOption(std::string_view long_option,
                    std::string_view default_value);

  CommandLineOption(std::string_view long_option, std::string_view short_option,
                    std::string_view default_value);

  /// Compare this to ther
  ///
  /// \return True if this long option equals other long option, false if not.
  // bool operator==(const CommandLineOption& other) const noexcept;

  /// Access the argument long option
  ///
  /// \return The argument long option
  std::string GetLongOption() const;

  /// Access the argument short option
  ///
  /// \return The argument short option
  std::string GetShortOption() const;

  /// Access the optional argument value as a given type
  ///
  /// \return The argument value as the given type
  template <typename T>
  T GetValue() const {
    return StringTo<T>(value_);
  }

  /// Set the optional argument value
  void SetValue(std::string_view value);  ///< [in] The argument value string

 private:
  std::string long_option_{};
  std::string short_option_{};
  std::string value_{};
};

/// Parse the given command line arguments
///
/// Passing two optional arguments with conflicting long/short names will
/// cause command line parsing errors.
void parse_args(
    int argc,            ///< [in] Number of command line arguments
    const char* argv[],  ///< [in] Arguments passed to the command line
    std::span<CommandLineArgument>
        arguments,  ///< [inout] Positional arguments names and values
    std::span<CommandLineOption>
        options);  ///< [inout] Optional arguments names and values

}  // namespace ccbuildutils
}  // namespace xykivo
