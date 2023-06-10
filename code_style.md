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

# Bazel

Follow the
[Bazel BUILD coding style](https://docs.bazel.build/versions/master/skylark/build-style.html)

# C/C++

Unless noted otherwise below, follow the
[C++ core guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)

Unless noted otherwise below, follow the
[Google C/C++ coding style](https://google.github.io/styleguide/cppguide.html)

In cases where the Google code style contradicts the C++ core guidelines prefer
the guideline from the C++ core guideline.

## Additions, Clarifications, and Modification to the Google Code Style

### C++20

All C++20 features are allowed.

### Use pragma once

Prefer using the #pragma once pre processor directive to header guards.

Rational:

The #pragma once directive is safer and easier to use. It is supported on most
modern compilers that support C++20.

### Doxygen Style Comments
Use Doxygen style comments to document classes, enums, functions and fields.
Rational:
* Being able to generate documentation in various formats may prove useful in
  the future
* Doxygen style comments provide a consistent easy to read documentation style

Doxygen style:
* Use /// as a doxygen comment line prefix
* Prefer to use ///< to document arguments, enum values and fields

### Use Exceptions for Errors
Use exceptions derived from std::exception to indicate an error.
Prefer using standard C++ exceptions from stdexcept.

Mark all functions that do not throw with noexcept modifier.

The noexcept modifier will let the caller know how errors are handled.

Rational:

Google code style forbids throwing exceptions. However the C++ core guidelines
recommend using them. In addition in the future the new
[C++ determinstic error specification](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0709r0.pdf)
may become part of the standard. If/when this happens, exception runtime and memory
usage may become deterministic.

### Pointer Alignment
Pointer (*) and reference (&) expressions must be aligned left.
Rational:
* This makes it easier to see the variable type for pointers and references

# Go
[Google Go coding style](https://google.github.io/styleguide/go/)

# Java

Follow the
[Google Java coding style](https://google.github.io/styleguide/javaguide.html).

# Kotlin

Follow the
[Kotlin Style Guide](https://kotlinlang.org/docs/reference/coding-conventions.html)

# Objective C

Follow the [Apple Coding Guidelines for Cocoa](https://developer.apple.com/library/archive/documentation/Cocoa/Conceptual/CodingGuidelines/CodingGuidelines.html#//apple_ref/doc/uid/10000146-SW1)

# Python

Follow the
[Python Style Guide](https://www.python.org/dev/peps/pep-0008/)

Use [YAPF](https://github.com/google/yapf) to format Python code.

# Shell script
Follow the
[Google Shell Style Guide](https://google.github.io/styleguide/shellguide.html)

# Swift
Fololow the
[Google Swift Style Guide](https://google.github.io/swift)
