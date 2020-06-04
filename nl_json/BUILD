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

load("@rules_cc//cc:defs.bzl", "cc_binary")

"""Code sample on how to use Niels Lohmann JSON library

Niels Lohmann JSON source code can be found at https://github.com/nlohmann/json
"""

cc_binary(
    name = "hellojson",
    srcs = glob([
        "src/*.cc",
        "src/*.h",
    ]),
    copts = [
        "-std=c++17",
        "-Ithird_party/nlohmann_json/include/",
    ],
    visibility = ["//visibility:private"],
    deps = [
        "//third_party/nlohmann_json",
    ],
)
