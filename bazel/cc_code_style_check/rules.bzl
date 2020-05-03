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

"""Rules to run code style tools on C++ targets.
"""

CcCodeStyleInfo = provider(
    doc = "Information for checking C++ files code style",
    fields = {
        "code_style_checker": "Path to the lint tool used",
        "code_style_config_files": "List of config files the lint tool uses",
        "cc_info": "C++ info of the C++ target linted",
    },
)

def _cc_code_style_check_impl(ctx):
    """Implementation of the cc_code_style_check rule (below)

    :param ctx: The cc_code_style_check rule context
    """
    toolchain = ctx.toolchains["//bazel/cc_code_style_check:toolchain_type"]
    args = ctx.actions.args()
    args.add(ctx.outputs.code_style_check_success)
    args.add_joined(ctx.files.srcs, join_with = ",")
    ctx.actions.run(
        outputs = [ctx.outputs.code_style_check_success],
        inputs = ctx.files.srcs + toolchain.code_style_config_files,
        executable = toolchain.code_style_checker,
        arguments = [args],
        use_default_shell_env = True,
        mnemonic = "CppCodeStyle",
        progress_message = "Running C++ code style checker on target {0}".format(
            ctx.attr.cc_target.label.name,
        ),
    )
    return [
        DefaultInfo(files = depset([ctx.outputs.code_style_check_success])),
        CcCodeStyleInfo(
            code_style_checker = toolchain.code_style_checker,
            code_style_config_files = toolchain.code_style_config_files,
            cc_info = ctx.attr.cc_target[CcInfo],
        ),
    ]

cc_code_style_check = rule(
    doc = "Run C++ code style check tool on a set of C++ sources",
    implementation = _cc_code_style_check_impl,
    attrs = {
        "srcs": attr.label_list(
            doc = "C++ source files whose code style is checked",
            allow_files = [".c", ".cc", ".cxx", ".cpp", ".h", ".hh", ".hxx", ".hpp"],
        ),
        "cc_target": attr.label(
            doc = "C++ target whose source files whose code style will be checked",
            mandatory = True,
            providers = [CcInfo],
        ),
        "code_style_check_success": attr.output(
            doc = "A file written to indicate the code style check succeeded",
            mandatory = True,
        ),
    },
    toolchains = ["//bazel/cc_code_style_check:toolchain_type"],
)
