# BSD 3-Clause License
#
# Copyright (c) 2020-2021, Dror Smolarsky
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
        inputs =
            ctx.files.srcs +
            toolchain.code_style_config_files,
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
