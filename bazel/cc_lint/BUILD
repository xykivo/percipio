# License
#
# Copyright (C) 2019-2020 Dror Smolarsky
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

"""C++ lint rules, toolchains and utilities
"""

load(":toolchain.bzl", "cc_lint_toolchain")

toolchain_type(
    name = "toolchain_type",
    visibility = ["//visibility:public"],
)

cc_lint_toolchain(
    name = "clang-tidy",
    linter = "//build_tools/cc:clang-tidy",
    # TODO(xykivo@gmail.com) Change the config files from absolute path to a
    #   search for the closet .clang-tidy and .clang-format up the directory
    #   tree from the lint target
    linter_config_files = [
        "//:.clang-tidy",
        "//:.clang-format",
    ],
    use_copts = True,
)

toolchain(
    name = "clang-tidy-toolchain",
    toolchain = ":clang-tidy",
    toolchain_type = ":toolchain_type",
)
