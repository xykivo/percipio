# BSD 3-Clause License
#
# Copyright (c) 2019-2021, Dror Smolarsky
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from
#    this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

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
        "-std=c++20",
        "-Wall",
        "-Werror",
        "-fno-rtti",
    ] + copts
    cc_args["copts"] = copts
    linkopts = cc_args.pop("linkopts", [])
    linkopts.extend(["-Wl,-warn_commons", "-Wl,-fatal_warnings"])
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
