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

"""Rules to run code style check tools on C++ targets.
"""

def _cc_code_style_check_toolchain_impl(ctx):
    """Implementation of the C++ code style toolchain rule
    """
    return platform_common.ToolchainInfo(
        code_style_checker = ctx.executable.code_style_checker,
        code_style_config_files = ctx.files.code_style_config_files,
    )

cc_code_style_check_toolchain = rule(
    implementation = _cc_code_style_check_toolchain_impl,
    doc = "C++ code style checker toolchain",
    attrs = {
        "code_style_checker": attr.label(
            doc = "Path to the code style checker tool executable",
            executable = True,
            mandatory = True,
            cfg = "host",
        ),
        "code_style_config_files": attr.label_list(
            doc = "List of code style tool configuration files",
            allow_empty = True,
            allow_files = True,
            mandatory = False,
        ),
    },
)
