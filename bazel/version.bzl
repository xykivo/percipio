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
