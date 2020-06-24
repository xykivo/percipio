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

# Common C++ bazel macros, rules and variables

load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library", "cc_test")
load("//bazel:version.bzl", "version_code")
load("//bazel/cc_code_style_check:rules.bzl", "cc_code_style_check")
load("//bazel/cc_lint:rules.bzl", "cc_lint")

def _add_common_cc_options(version, **kwargs):
    """Add common C++ defines, compiler and linker options.

    This function will add common Xykivo C++ options to the given cc_library
    or cc_binary optional arguments.

    :param version: The version of the of the C++ target
    :param kwargs: Optional C++ target arguments
    """
    cc_args = kwargs
    local_defines = cc_args.pop("local_defines", [])
    local_defines.append("XKV_VERSION=%s" % version_code(version))
    cc_args["local_defines"] = local_defines
    copts = cc_args.pop("copts", [])
    copts = [
        "-std=c++17",
        "-Wall",
        "-Werror",
        "-fno-rtti",
        "-fno-exceptions",
    ] + copts
    cc_args["copts"] = copts
    linkopts = cc_args.pop("linkopts", [])
    linkopts.extend(["-Wl,--warn-common", "-Wl,--fatal-warnings"])
    cc_args["linkopts"] = linkopts
    return cc_args

def _add_cc_lint_targets(name, test_only, **kwargs):
    """Add C++ lint and code style check targets for the given C++ target

    :param name: Name of the C++ target
    :param kwargs: Optional C++ target arguments
    """
    cc_target = ":" + name
    srcs = kwargs.pop("srcs", [])
    hdrs = kwargs.pop("hdrs", [])
    cc_code_style_check(
        name = name + "-code-style-check",
        srcs = srcs + hdrs,
        cc_target = cc_target,
        code_style_check_success = "cc_code_style_check_succeeded",
        testonly = test_only,
    )
    cc_lint(
        name = name + "-lint",
        srcs = srcs + hdrs,
        cc_target = cc_target,
        copts = kwargs["copts"],
        lint_success = "cc_lint_succeeded",
        testonly = test_only,
    )

def xkv_cc_binary(
        name,
        version,
        **kwargs):
    """Xykivo C++ binary macro

    Adds common Xykvo C++ arguemnts and compiler/linker options to the C++
    binary rule.
    Add a C++ code style check rule on all the binary source files.
    Add a C++ lint check rule on all the binary source files.
    :param name: The name of the C++ binary target
    :param version: The C++ binary version string
    :param kwargs: C++ binary rule arguments
    """
    cc_args = _add_common_cc_options(version, **kwargs)
    cc_binary(name = name, **cc_args)
    _add_cc_lint_targets(name, False, **cc_args)

def xkv_cc_library(
        name,
        version,
        **kwargs):
    """Xykivo C++ library macro

    Adds common Xykvo C++ arguemnts and compiler/linker options to the C++
    library rule.
    Add a C++ code style check rule on all the library source files.
    Add a C++ lint check rule on all the library source files.
    :param name: The name of the C++ library target
    :param version: The C++ library version string
    :param kwargs: C++ library rule arguments
    """
    cc_args = _add_common_cc_options(version, **kwargs)
    cc_library(name = name, **cc_args)
    _add_cc_lint_targets(name, False, **cc_args)

def xkv_cc_test(
        name,
        version,
        **kwargs):
    """Xykivo C++ test macro

    Adds common Xykvo C++ arguemnts and compiler/linker options to the C++
    test rule.
    Add a C++ code style check rule on all the test source files.
    Add a C++ lint check rule on all the test source files.
    :param name: The name of the C++ test target
    :param version: The C++ test version string
    :param kwargs: C++ test rule arguments
    """
    cc_args = _add_common_cc_options(version, **kwargs)
    cc_test(name = name, **cc_args)
    _add_cc_lint_targets(name, True, **cc_args)
