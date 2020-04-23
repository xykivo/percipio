# License

Copyright (C) 2020 Dror Smolarsky

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a [copy](license.md) of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Bazel

Follow the
[Bazel BUILD coding style](https://docs.bazel.build/versions/master/skylark/build-style.html)

# C/C++

Unless noted otherwise below, follow the
[Google C/C++ coding style](https://google.github.io/styleguide/cppguide.html)

## Additions, Clarifications, and Modification to the Google Code Style

### Doxygen Style Comments
Use Doxygen style comments to document classes, enums, functions and fields.  
Rational:  
* Being able to generate documentation in various formats may prove useful in
  the future
* Doxygen style comments provide a consistent easy to read documentation style

Doxygen style:  
* Use /// as a doxygen comment line prefix
* Prefer to use ///< to document arguments, enum values and fields

### Use noexcept
Mark all functions with noexcept modifier.  
Rational:
Google code style forbids throwing exceptions. However in the future the new
[C++ determinstic error specification](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0709r0.pdf)
may become part of the standard. If/when this happens, using deterministic
return value exceptions will be allowed.  
The noexcept modifier will let the caller know how errors are handled.

### Pointer Alignment
Pointer (*) and reference (&) expressions must be aligned left.
Rational:
* This makes it easier to see the variable type for pointers and references

# Java

Follow the
[Google Java coding style](https://google.github.io/styleguide/javaguide.html).

# Kotlin

Follow the
[Kotlin Style Guide](https://kotlinlang.org/docs/reference/coding-conventions.html)

# Python

Follow the
[Python Style Guide](https://www.python.org/dev/peps/pep-0008/)
