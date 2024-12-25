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

"""Xykivo percipio Metal draw primitives (triangle) example.

See: https://developer.apple.com/documentation/metal/using_a_render_pipeline_to_render_primitives?language=objc
"""

load("@rules_apple//apple:macos.bzl", "macos_application")
load("@rules_apple//apple:versioning.bzl", "apple_bundle_version")
load("@rules_metal//:metal.bzl", "metal_binary")

metal_binary(
    name = "m02drawtrishaders",
    srcs = glob([
        "shader/**/*.metal"
    ]) + ["src/common_types.h"],
    visibility = ["//visibility:private"],
)

# Note: the ObjC & Metal header common_types.h file must be placed in the src
# directory, since objc_library rules relative include paths specified with
#  -I or -quote, use the generated XCode project directory as the root path,
# and not the source directory.
# See https://bazel.build/reference/be/objective-c#objc_library copts parameter
# descripttion.
# This prevents placing this file in an include path
objc_library(
    name = "m02drawtri",
    srcs = glob([
        "src/**/*.h",
        "src/**/*.m",
    ]),
    enable_modules = True,
    # The default module name is the full path to the target delimited by '_':
    # objc_metal_tour_m02drawtri
    module_name = "m02drawtri",
    target_compatible_with = select({
            "@platforms//os:osx": [],
            "//conditions:default": ["@platforms//:incompatible"],
    }),
    linkopts = ["-framework Metal", "-framework MetalKit"],
    data = [":m02drawtrishaders"],
    visibility = ["//visibility:private"],
)

apple_bundle_version(
    name = "m02drawtriversion",
    build_version = "0.0",
    visibility = ["//visibility:private"],
)

macos_application(
    name = "m02drawtriapp",
    bundle_id = "com.xykivo.percipio.hello-cocoa",
    infoplists = [":Info.plist"],
    minimum_os_version = "11",
    version = ":m02drawtriversion",
    deps = [":m02drawtri"],
    target_compatible_with = select({
            "@platforms//os:osx": [],
            "//conditions:default": ["@platforms//:incompatible"],
    }),
    visibility = ["//visibility:private"],
)
