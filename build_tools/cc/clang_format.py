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

'''Run clang-format (located in the system path) on set of C++ source files.
'''

import argparse
import shutil
import subprocess
import xml.dom.minidom


def _which_clang_format():
    '''Locate clang-format in the local system path
    '''
    clang_format_binary = shutil.which('clang-format')
    if clang_format_binary is None:
        raise Exception('Failed to find clang-format in system path')
    return clang_format_binary


def _run_clang_format(clang_format_binary, src_files):
    '''Run clang-format executable on the given set of source files
    '''
    clang_format_args = [
        clang_format_binary,
        '--color',
        '--output-replacements-xml',
        '--style=file']
    clang_format_args.extend(src_files)
    clang_format_result = subprocess.run(
        clang_format_args, stdout=subprocess.PIPE, encoding='utf-8')
    XML_FILE_VERSION = r"<?xml version='1.0'?>"
    style_errors = False
    for src, xml_output_string in list(zip(
            src_files, clang_format_result.stdout.split(XML_FILE_VERSION)[1:])):
        xml_output = xml.dom.minidom.parseString(
            XML_FILE_VERSION + xml_output_string)
        for replacement in xml_output.getElementsByTagName('replacement'):
            # TODO(xykivo@gmail.com) Find a way to print error line and column
            #   without having to open the source file
            print('Code style error in', src, 'in offset',
                  replacement.getAttribute('offset'))
            style_errors = True
    if 0 != clang_format_result.returncode or style_errors:
        raise Exception('C++ code style check using clang format failed')


def _write_code_style_check_succeeded_file(lint_succeeded, src_files):
    '''Write the code style check succeded file

    Write a list of C++ src files for which the code style check succeeded to
    the file.
    '''
    code_style_check_succeeded_file = open(lint_succeeded, 'w')
    for src_file in src_files:
        code_style_check_succeeded_file.write(
            'C++ code style check of {0} succeeded\n'.format(src_file))
    code_style_check_succeeded_file.close()


if '__main__' == __name__:
    arg_parser = argparse.ArgumentParser(description=__doc__)
    arg_parser.add_argument(
        'code_style_check_succeeded', metavar='CODE_STYLE_CHECK_SUCCEEDED',
        help='File written to mark C++ code style check succeeded on all source files')
    arg_parser.add_argument(
        'src_files', metavar='SRC_FILES',
        help='C++ source whose code style is checked. Files are delimited by ,')
    args = arg_parser.parse_args()
    clang_format_binary = _which_clang_format()
    src_files = args.src_files.split(',')
    _run_clang_format(clang_format_binary, src_files)
    _write_code_style_check_succeeded_file(
        args.code_style_check_succeeded, src_files)
    exit(0)
