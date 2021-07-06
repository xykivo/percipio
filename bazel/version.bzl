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

# Common version Bazel macros, rules and variables

def version_code(version_string):
    """
    Get version code from version string
    """
    DEV_VERSION_STATUS_CODE = 0x0  # development version code
    BETA_VERSION_STATUS_CODE = 0x1  # beta release version code
    RC_VERSION_STATUS_CODE = 0x2  # release candiate version code
    RELEASE_VERSION_STATUS_CODE = 0x3  # final release version code
    MAX_STATUS = 4
    MAX_VERSION = 1024
    VERSION_SHIFTS = [
        MAX_STATUS * MAX_VERSION * MAX_VERSION,  # major version shift
        MAX_STATUS * MAX_VERSION,  # minor version shift
        MAX_STATUS,
    ]  # patch version shift
    VERSION_STRING_ERROR_MSG = \
        "Error: version string format must be X.X.X [dev|beta|rc]"

    version_components = version_string.split("-")
    if 2 < len(version_components):
        fail(VERSION_STRING_ERROR_MSG)
    version = RELEASE_VERSION_STATUS_CODE
    if 2 == len(version_components):
        if "dev" == version_components[1]:
            version = DEV_VERSION_STATUS_CODE
        elif "beta" == version_components[1]:
            version = BETA_VERSION_STATUS_CODE
        elif "rc" == version_components[1]:
            version = RC_VERSION_STATUS_CODE
        else:
            fail(VERSION_STRING_ERROR_MSG)
    version_numbers = version_components[0].split(".")
    if 3 != len(version_numbers):
        fail(VERSION_STRING_ERROR_MSG)
    for vni in [0, 1, 2]:
        vn = int(version_numbers[vni])
        if 0 > vn:
            fail("Error: version numbers must not be negative")
        if MAX_VERSION <= vn:
            fail("Error: version number must be lower than " + MAX_VERSION)
        version = version + (vn * VERSION_SHIFTS[vni])
    return version
