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
