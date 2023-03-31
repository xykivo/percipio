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

"""Rules to run lint tools on C++ targets
"""

load("@rules_cc//cc:toolchain_utils.bzl", "find_cpp_toolchain")

CcLintInfo = provider(
    doc = "Information for linting C++ files",
    fields = {
        "linter_path": "Path to the lint tool used",
        "linter_config_files": "List of config files the lint tool uses",
        "cc_info": "C++ info of the C++ target linted",
    },
)

def _cc_compiler_opts(cc_toolchain, cc_info, copts):
    """Get a list of the C++ compiler options

    :param ctx: The cc_lint rule context
    """
    cc_compilation_context = cc_info.compilation_context
    cc_include_dirs = \
        cc_toolchain.built_in_include_directories + \
        cc_compilation_context.framework_includes.to_list() + \
        cc_compilation_context.includes.to_list() + \
        cc_compilation_context.quote_includes.to_list() + \
        cc_compilation_context.system_includes.to_list()
    compiler_options = []
    compiler_options.extend(
        ["-I" + inc_dir for inc_dir in cc_include_dirs],
    )
    compiler_options.extend(
        ["-D" + cc_def for cc_def in cc_compilation_context.defines.to_list()],
    )
    compiler_options.extend(
        ["-D" + cc_def for cc_def in cc_compilation_context.local_defines.to_list()],
    )
    if (cc_toolchain.needs_pic_for_dynamic_libraries):
        compiler_options.append("-fPIC")
    compiler_options.extend(copts)
    return compiler_options

def _cc_lint_impl(ctx):
    """Implementation of the cc_lint rule (below)

    :param ctx: The cc_lint rule context
    """
    toolchain = ctx.toolchains["//bazel/cc_lint:toolchain_type"]
    args = ctx.actions.args()
    args.add(ctx.outputs.lint_success)
    args.add_joined(ctx.files.srcs, join_with = ",")
    if toolchain.use_copts:
        args.add("--copts")
        args.add_joined(
            _cc_compiler_opts(
                find_cpp_toolchain(ctx),
                ctx.attr.cc_target[CcInfo],
                ctx.attr.copts,
            ),
            omit_if_empty = True,
            join_with = ",",
        )
    ctx.actions.run(
        outputs = [ctx.outputs.lint_success],
        inputs =
            ctx.files.srcs +
            toolchain.linter_config_files +
            ctx.attr.cc_target[CcInfo].compilation_context.headers.to_list(),
        executable = toolchain.linter,
        arguments = [args],
        use_default_shell_env = True,
        mnemonic = "CppLint",
        progress_message = "Running C++ lint on target {0}".format(
            ctx.attr.cc_target.label.name,
        ),
    )
    return [
        DefaultInfo(files = depset([ctx.outputs.lint_success])),
        CcLintInfo(
            linter_path = toolchain.linter,
            linter_config_files = toolchain.linter_config_files,
            cc_info = ctx.attr.cc_target[CcInfo],
        ),
    ]

cc_lint = rule(
    doc = "Run C++ lint tool on a set of C++ sources",
    implementation = _cc_lint_impl,
    attrs = {
        "srcs": attr.label_list(
            doc = "C++ source files linted",
            allow_files = [".c", ".cc", ".cxx", ".cpp", ".h", ".hh", ".hxx", ".hpp"],
        ),
        "cc_target": attr.label(
            doc = "C++ target whose source files will be linted",
            mandatory = True,
            providers = [CcInfo],
        ),
        "copts": attr.string_list(doc = "C++ compiler options"),
        "lint_success": attr.output(
            doc = "A file written to indicate the lint test succeeded",
            mandatory = True,
        ),
        "_cc_toolchain": attr.label(
            default = Label("@bazel_tools//tools/cpp:current_cc_toolchain"),
        ),
    },
    toolchains = ["//bazel/cc_lint:toolchain_type"],
)
