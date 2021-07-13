# License

BSD 3-Clause License

Copyright (c) 2020-2021, Dror Smolarsky
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

# About

This is a code sample that tries to illustrate that Bazel uses the -isystem
option for include paths exported from a cc_library target includes argument.

The -isystem is generally reserved for compiler or system headers, and has
a different behavior than include paths that are used with the -I compiler
option.

This sameple has 2 sub project

* use_includes: uses the cc_library includes argument to set the include paths
  in all C++ targets that depend on a library
* use_copts: uses the cc_library and cc_binary copts argument to set the include
  paths, which requires each C++ target to have knowledege of all the C++
  libraries it depends on directly or indirectly

The dependecy graph for both samples is:

app <- bar <- foo

* app depends on bar
* bar depends on foo

# Building

Compilation for both options fails on purpose when compiling the app target.
This makes it wasy to view the compile options uses when compiling app by using
the --verbose_failures options when building app.

* To build the use_includes sample run:
  bazel build //issues/bzl_cc_libs_includes/use_includes/app --verbose_failures

# Include Options

## Use includes option

Include options used when compiling app in the use_includes sample:

-iquote bazel-out/k8-fastbuild/bin
-iquote external/bazel_tools
-iquote bazel-out/k8-fastbuild/bin/external/bazel_tools

-isystem issues/bzl_cc_libs_includes/use_includes/bar/include
-isystem bazel-out/k8-fastbuild/bin/issues/bzl_cc_libs_includes/use_includes/bar/include
-isystem issues/bzl_cc_libs_includes/use_includes/foo/include
-isystem bazel-out/k8-fastbuild/bin/issues/bzl_cc_libs_includes/use_includes/foo/include

As can be seen above the foo include path is passed transitively when compiling
app, but it uses the -isystem option.
This is because foo sets its include path in the includes argument of its
cc_library target.

## Use copts option

TODO
