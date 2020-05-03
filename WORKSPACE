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

# Xykivo repo workspace

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Python

RULES_PYTHON_SHA = \
    "aa96a691d3a8177f3215b14b0edc9641787abaaa30363a080165d06ab65e1161"

RULES_PYTHON_VERSION = "0.0.1"

http_archive(
    name = "rules_python",
    sha256 = RULES_PYTHON_SHA,
    url = "https://github.com/bazelbuild/rules_python/releases/download/{0}/rules_python-{0}.tar.gz".format(RULES_PYTHON_VERSION),
)

load("@rules_python//python:repositories.bzl", "py_repositories")

py_repositories()

# JVM external rules - needed for load of maven_install below
RULES_JVM_EXTERNAL_VERSION = "3.0"

RULES_JVM_EXTERNAL_SHA = \
    "62133c125bf4109dfd9d2af64830208356ce4ef8b165a6ef15bbff7460b35c3a"

http_archive(
    name = "rules_jvm_external",
    sha256 = RULES_JVM_EXTERNAL_SHA,
    strip_prefix = "rules_jvm_external-%s" % RULES_JVM_EXTERNAL_VERSION,
    url = "https://github.com/bazelbuild/rules_jvm_external/archive/%s.zip" %
          RULES_JVM_EXTERNAL_VERSION,
)

# Maven repositories
load("@rules_jvm_external//:defs.bzl", "maven_install")

maven_install(
    artifacts = [
        "com.google.truth:truth:1.2.0",
        "junit:junit:4.12",
    ],
    repositories = [
        "https://maven.google.com",
        "https://jcenter.bintray.com",
    ],
)

# C++ lint and code style tools
register_toolchains(
    "//bazel/cc_lint:clang-tidy-toolchain",
    "//bazel/cc_code_style_check:clang-format-toolchain",
)
