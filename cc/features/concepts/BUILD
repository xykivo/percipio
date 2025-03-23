# License
#
# Copyright (C) 2025 Dror Smolarsky
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

"""C++ concepts code samples package

C++ reference pages:
- https://en.cppreference.com/w/cpp/language/constraints
- https://en.cppreference.com/w/cpp/language/requires
- https://en.cppreference.com/w/cpp/header/concepts
"""

load("//bazel:cc.bzl", "xkv_cc_binary")

xkv_cc_binary(
    name = "ccconcepts",
    srcs = glob(["src/*.cc"]),
    copts = [],
    version = "0.0.0",
    visibility = ["//visibility:private"],
    deps = [],
)
