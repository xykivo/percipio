# License
#
# Copyright (C) 2020 Dror Smolarsky
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

"""C++ code sytle rules, toolchains and utilities
"""

load(":toolchain.bzl", "cc_code_style_check_toolchain")

toolchain_type(
    name = "toolchain_type",
    visibility = ["//visibility:public"],
)

cc_code_style_check_toolchain(
    name = "clang-format",
    code_style_checker = "//build_tools/cc:clang-format",
    # TODO(xykivo@gmail.com) Change the config files from absolute path to a
    #   search for the closet .clang-format up the directory tree from the lint
    #   target
    code_style_config_files = [
        "//:.clang-format",
    ],
)

toolchain(
    name = "clang-format-toolchain",
    toolchain = ":clang-format",
    toolchain_type = ":toolchain_type",
)
