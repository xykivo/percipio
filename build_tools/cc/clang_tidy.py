#!/usr/bin/python3
# -*- coding: utf-8 -*-

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

'''Run clang-tidy (located in the system path) on set of C++ source files.
'''

import argparse
import shutil
import subprocess


def _which_clang_tidy():
    '''Locate clang-tidy in the local system path
    '''
    clang_tidy_binary = shutil.which('clang-tidy')
    if clang_tidy_binary is None:
        raise Exception('Failed to find clang-tidy in system path')
    return clang_tidy_binary


def _run_clang_tidy(clang_tidy_exe, src_files, copts):
    '''Run clang-tidy executable on the given set of source files
    '''
    clang_tidy_args = [clang_tidy_exe]
    clang_tidy_args.extend(src_files)
    clang_tidy_args.extend(['--', '-x', 'c++'])
    clang_tidy_args.extend(copts)
    clang_tidy_result = subprocess.run(clang_tidy_args)
    if 0 != clang_tidy_result.returncode:
        raise Exception('C++ lint using clang tidy failed')


def _write_lint_succeeded_file(lint_succeeded, src_files):
    '''Write the lint succeded file

    Write a list of C++ src files for which the lint check succeeded to the
    file.
    '''
    lint_succeeded_file = open(lint_succeeded, 'w')
    for src_file in src_files:
        lint_succeeded_file.write(
            'C++ lint of {0} succeeded\n'.format(src_file))
    lint_succeeded_file.close()


if '__main__' == __name__:
    print('hello')
    arg_parser = argparse.ArgumentParser(description=__doc__)
    arg_parser.add_argument(
        'lint_succeeded', metavar='LINT_SUCCEEDED',
        help='File written to mark C++ lint succeeded on all source files')
    arg_parser.add_argument(
        'src_files', metavar='SRC_FILES',
        help='C++ source file linted. Files are delimited by ,')
    arg_parser.add_argument(
        '--copts', metavar='COPTS', action='store',
        help='C++ compiler options prefixed by "copts=" and delimited by ,')
    args = arg_parser.parse_args()
    clang_tidy_binary = _which_clang_tidy()
    print('DBG', clang_tidy_binary)
    src_files = args.src_files.split(',')
    copts = args.copts.replace('copts=', '').split(',')
    _run_clang_tidy(clang_tidy_binary, src_files, copts)
    _write_lint_succeeded_file(args.lint_succeeded, src_files)
    exit(0)
