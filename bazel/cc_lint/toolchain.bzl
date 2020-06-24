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

"""C++ lint toolchains
"""

def _cc_lint_toolchain_impl(ctx):
    """Implementation of the C++ lint toolchain rule
    """
    return platform_common.ToolchainInfo(
        linter = ctx.executable.linter,
        linter_config_files = ctx.files.linter_config_files,
        use_copts = ctx.attr.use_copts,
    )

cc_lint_toolchain = rule(
    implementation = _cc_lint_toolchain_impl,
    doc = "C++ Linter toochain information",
    attrs = {
        "linter": attr.label(
            doc = "Path to the lint tool executable",
            executable = True,
            mandatory = True,
            cfg = "host",
        ),
        "linter_config_files": attr.label_list(
            doc = "List of lint tool configuration files",
            allow_empty = True,
            allow_files = True,
            mandatory = False,
        ),
        "use_copts": attr.bool(
            doc = "True if the lint tool makes use of C++ compiler options",
            default = True,
            mandatory = False,
        ),
    },
)
