# BSD 3-Clause License
#
# Copyright (c) 2023, Dror Smolarsky
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

"""Xykivo percipio Objective-C hello Cocoa

Create a simple Cocoa window and display something in it using Objective-C.
Use a Swift binary to run the Objective-C window code.
"""

load("@build_bazel_rules_apple//apple:macos.bzl", "macos_application")
load("@build_bazel_rules_apple//apple:versioning.bzl", "apple_bundle_version")

objc_library(
    name = "xkvhellococoa",
    hdrs = glob(["include/**/*.h"]),
    srcs = glob([
        "src/**/*.h",
        "src/**/*.m",
    ]),
    enable_modules = True,
    # The default module name is the full path to the target delimited by '_':
    # objc_tour_hello_cocoa_xkvhellococoa
    module_name = "xkvhellococoa",
    target_compatible_with = select({
            "@platforms//os:osx": [],
            "//conditions:default": ["@platforms//:incompatible"],
    }),
)

apple_bundle_version(
    name = "xkvhellococoaversion",
    build_version = "0.0",
)

macos_application(
    name = "xkvhellococoaapp",
    bundle_id = "com.xykivo.percipio.hello-cocoa",
    infoplists = [":Info.plist"],
    minimum_os_version = "11",
    version = ":xkvhellococoaversion",
    deps = [":xkvhellococoa"],
    target_compatible_with = select({
            "@platforms//os:osx": [],
            "//conditions:default": ["@platforms//:incompatible"],
    }),
)
