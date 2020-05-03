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
            ["copts="] + _cc_compiler_opts(
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
