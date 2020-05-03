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

"""C++ build utilities
"""

load("@rules_python//python:defs.bzl", "py_binary")

# Wrapper to run clang-tidy lint tool for C++ targets
py_binary(
    name = "clang-tidy",
    srcs = ["clang_tidy.py"],
    main = "clang_tidy.py",
    python_version = "PY3",
    visibility = ["//visibility:public"],
)

# Wrapper to run clang-tidy lint tool for C++ targets
py_binary(
    name = "clang-format",
    srcs = ["clang_format.py"],
    main = "clang_format.py",
    python_version = "PY3",
    visibility = ["//visibility:public"],
)
