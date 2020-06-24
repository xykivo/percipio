#!/usr/bin/python3
# -*- coding: utf-8 -*-

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
