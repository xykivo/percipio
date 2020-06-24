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

# Repository

The git repo must not contain any binary blobs.
This includes, but not limited to, libraries, Office files, images, resources,
etc.
The repository should contain only source files, scripts, md docs, text files,
xml files etc.
As a general rule if a file can be edited in a text editor, and diffed using the
diff utility it can be added to the repo.
This will insure fast performance when forking, diffing and posting reviews.

# Live at Head

Master and version branches must always be stable. This means any commit can be
used to create a release.

Each feature and bug fix should be developed in a separate branch.
Once the feature or bug fix is code complete and tested it should be merged back
to the master branch.
When merging back to the master branch
  * Make sure all features and functionality are tested (not just the feature
    under development). This means the full set of tests for the entire
    repository must pass.
  * All features, and module interfaces should have automated tests.
    In cases where automated testing is not possible, or has not been
    implemented yet, document the test procedure in the
    [testing doc](testing.md).
  * All merges back the master or version branches must use the --no-ff option
  * Full build and test should always work the master and version branches  
    bazel build //...
    bazel test //...

Commit early and often. Commit small self contained changes.
Each commit must compile and all tests must pass (in-development test warnings
allowed).
The master branch should be kept up to date with the upstream master branch.
If the merge from a feature branch to the master/version branch is not trivial
it is recommended to merge from the master/version branch to the feature branch
first, resolve any merge issues in the feature branch, and then merge back to
the master/version branch.

# Lint and Code Style Check

## C++

Every xykivo C++ target will also have a C++ lint, and C++ code style targets
(generated through the xykvio C++ rule).
The C++ lint rule uses the clang-tidy toolchain, which requires that clang-tidy
be in the system path.
The C++ code style check uses the clang-format toolchain, which require that
clang-format be in the system path.

## Python

It is recommended to run C++ code style and lint checks.

# Versions

Most targets in the repository are not expected to have an form of versioning.
However for some cases versions may be useful.

Follow [semantic versioning](https://semver.org/) guidelines.
Versions for all components use a 3 version numbers system, separated by '.'
* Major version number
* Minor version number
* Patch version number
* Version status: can be one of -dev, -alpha, -beta or none of these

Version format: Major.minor.patch
E.g. 0.0.0

Each version major.minor version for a component should have a branch in the
git repository.

Major version change implies a major behavior and/or interface change. There is
no guarantee of backward compatibility. A large collection of minor changes
can also be treated as a major version.

Minor version change imply a minor behavior change, or collection of patches.
Bacward compatibility is guaranteed.

Patch version change imply a bug fix. Backward compatibility is guaranteed.
