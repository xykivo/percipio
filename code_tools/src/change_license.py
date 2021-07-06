#!/usr/bin/python3
# -*- coding: utf-8 -*-

# BSD 3-Clause License
#
# Copyright (c) 2021, Dror Smolarsky
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

'''Modify source code license.

Modify source code license from the current license to the provided target
license.

License comments in source (Bazel, C++, python) files will be converted to the
new license.
If the root directory the script runs from contains a LICENSE, LICENSE.md, or
LICENSE.txt file the content of this file will be replaced with the new license.

Assumptions:
* License comments appear first in the file (except for optional shebang and
  encoding comments)
* License files contain exactly one and only one license, and nothing else
'''

import argparse
import datetime
import os
import re

import bsd_3_clause_license
import gpl3_license
import mit_license

PATH_ARG_HELP_MSG = '''Path to the files to convert

If path is a single file only that file license comment will be modifed.
If path is a directory than the license comment in all files in the directory
and all sub directories will be modifed.
'''
SHEBANG_COMMENT = r'#!/usr/bin/(?P<language>\w+)'
ENCODING_COMMENT = r'# -\*- coding: (?P<encoding>[\w\-]+) -\*-'
LICESNES = {
    'bsd3': bsd_3_clause_license.BSD_LICENSE_3_CLAUSE,
    'gpl3': gpl3_license.GPL3_LICENSE_NOTICE,
    'mit': mit_license.MIT_LICENSE_CLAUSE
}


def get_license_lines_range(source_file_lines, comment_prefix):
    '''Get the inclusive range of lines = [begin, end] that contain the license
    comment

    This function assumes the license comment is the first thing in the file
    after any optional shebang and encoding line comments.
    This function assumes there is an empty line after the shebang or encoding
    comment.
    This function assumes there is an empty lines after the license comment.

    :param source_file_lines: The content of the source file provided as a
                              sequence of lines
    :param comment_prefix: The string pattern that mark a line comment in the
                           code
    '''
    begin = 0
    if len(source_file_lines) > begin:
        if re.match(SHEBANG_COMMENT, source_file_lines[begin]) is not None:
            begin = begin + 1
        if re.match(ENCODING_COMMENT, source_file_lines[begin]) is not None:
            begin = begin + 1
    while '\n' == source_file_lines[begin]:
        begin = begin + 1
    end = begin
    while '\n' != source_file_lines[end]:
        end = end + 1
    return begin, end


def license_re(license):
    '''Convert a license text into a licese regular expression used to match
    license comments in source files, or license text in a file.

    The license text input is assumed to have regular expression syntax embedded
    into to it.

    :returns: regular expression to match text to the given license
    :param license: the license text
    '''
    return re.sub(r'\s+', ' ', ' '.join(license))


def is_license_notice(license_notice_re, license_notice, comment_prefix):
    '''Check if the given license notice comment matches the given license
    regular expression

    :param license_notice_re: The license notice regular expression
    :param license_notice: The license notice comment
    :param comment_prefix: The coding language comment prefix
    :returns: True, copyright year, and copyright orner if the given license
              comment matches the given license comment, false, none and noe if
              not
    '''
    LINE_SEPARATOR_MARKER = r'==='
    license_text = re.sub(
        r'{0}{1} ?'.format(LINE_SEPARATOR_MARKER, comment_prefix),
        '',
        LINE_SEPARATOR_MARKER + LINE_SEPARATOR_MARKER.join(
            license_notice))
    license_text = re.sub('\s+', ' ', license_text)
    match = re.match(license_notice_re, license_text)
    if match is not None:
        return True, match.group('year'), match.group('copyright_owner')
    return False, None, None


def license_re_to_license_comment(
        license_notice_re, comment_prefix, year, owner):
    '''Convert a license comment regular expression to a license comment

    :param license_notice_re: the license regular expression
    :param comment_prefix: the coding language line comment prefix to use
    :param year: the license copyright year
    :param owner: the license copyright owner
    :returns: the license comment with a year range that ends this year and the
              owner name
    '''
    license_comment = '\n'.join(license_notice_re)
    license_comment = re.sub(r'\\\(', r'(', license_comment)
    license_comment = re.sub(r'\\\)', r')', license_comment)
    license_comment = re.sub(r'\(\?\:', r'', license_comment)
    license_comment = re.sub(r'\)\?', r'', license_comment)
    license_comment = re.sub(r'\\\.', r'.', license_comment)
    current_year = datetime.date.today().year
    copyright_year = str(current_year)
    match = re.match(r'(?:(\d+)\-)?(\d+)', year)
    if match[1] is None:
        if int(match[2]) < int(current_year):
            copyright_year = '{0}-{1}'.format(match[2], current_year)
    else:
        copyright_year = '{0}-{1}'.format(match[1], current_year)
    license_comment = re.sub(
        r'\(\?P\<year\>\[\\d\\\-\]\+\)', copyright_year, license_comment)
    license_comment = re.sub(
        r'\(\?P\<copyright_owner\>\[\\w\\s\]\+\)', owner, license_comment)
    line_prefix = comment_prefix + ' '
    license_comment = line_prefix + \
        re.sub(r'\n', '\n' + line_prefix, license_comment)
    license_comment = re.sub(
        line_prefix + '\n', comment_prefix + '\n', license_comment)
    license_comment = re.sub(comment_prefix + r' $', '', license_comment)
    return license_comment


def change_source_file_license(path, comment_prefix, new_license_name):
    '''Change the license comment in a source code file

    This function assumes the license comment is the first thing in the file
    after any optional shebang and encoding line comments.

    This function assumes that path is a valid path to file.

    :param path: path to the file
    :param comment_prefix: the string pattern that mark a line comment in the
                           code
    :param new_license_name: the name of the new license to use in the given
                             source file
    '''
    new_source_file_lines = None
    with open(path, 'r') as source_file:
        source_file_lines = source_file.readlines()
        license_begin, license_end = get_license_lines_range(
            source_file_lines, comment_prefix)
        for license_name, license in LICESNES.items():
            is_license_comment, year, owner = is_license_notice(
                license_re(license),
                source_file_lines[license_begin: license_end],
                comment_prefix)
            if is_license_comment:
                if license != license_name:
                    new_source_file_lines = source_file_lines.copy()
                    # TODO(xykivo#67) Instead of using hard coded BSD-3 license
                    #     as the replacement license, pass a replacement license
                    #     argument
                    new_source_file_lines[license_begin: license_end] =\
                        license_re_to_license_comment(
                            # bsd_3_clause_license.BSD_LICENSE_3_CLAUSE,
                            LICESNES[new_license_name],
                            comment_prefix,
                            year,
                            owner)
                break
        # Exactly 1 license in the LICENSE map must match, when a
        # match is found the function succeeds
        if new_source_file_lines is None:
            raise Exception('Unsupported license notice comment in', path)
    # print(''.join(new_source_file_lines))
    with open(path, 'w') as source_file:
        source_file.writelines(new_source_file_lines)


def change_file_license(path, new_license_name):
    '''Change the license of the file at the given path

    If path is a license file the license in the file will be changed to the
    new license.
    If path is a source file the license comment in the file will changed to
    the new license. Only Bazel, C/C++ and Python source files are supported.

    :param path: path to the file whose license is changed
    :param new_license_name: the name of the new license to use in the given
                             source file
    '''
    file_name = os.path.split(path)[1]
    ext = os.path.splitext(file_name)[1]
    if ('.bzl' == ext) or ('WORKSPACE' == file_name) or ('BUILD' == file_name):
        change_source_file_license(path, '#', new_license_name)
    elif ('.h' == ext) or ('.cc' == ext):
        change_source_file_license(path, r'//', new_license_name)
    elif '.py' == ext:
        change_source_file_license(path, r'#', new_license_name)


def change_dir_license(path, new_license_name):
    '''Recursilvely change the license of all license files and source files
    under the given direcotry path

    :param path: path to the direcotry that contains source files whose
                 license will be changed
    :param new_license_name: the name of the new license to use in the given
                             source file
    '''
    for child in os.listdir(path):
        child_path = os.path.join(path, child)
        if os.path.isdir(child_path):
            change_dir_license(child_path, new_license_name)
        elif os.path.isfile(child_path):
            change_file_license(child_path, new_license_name)


def change_license(path, new_license_name):
    '''Change the license file, and license comment in all sources in the path.

    If path is a license file the license in the file will be changed to the
    new license.
    If path is a source file the license comment in the file will changed to
    the new license.
    If path is a directory, then all license files and license comments in
    source files under the directory will be recursilvely replaced with the new
    license.

    :param path: path to the direcotry or file whose license is changed
    :param new_license_name: the name of the new license to use in the given
                             source file
    '''
    if os.path.isfile(args.path):
        change_file_license(args.path, new_license_name)
    elif os.path.isdir(args.path):
        change_dir_license(args.path, new_license_name)
    else:
        raise Exception('The path argument must be a file or directory')


if '__main__' == __name__:
    arg_parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter)
    arg_parser.add_argument(
        'license', help='The license converted to', choices=LICESNES.keys())
    arg_parser.add_argument('path', help=PATH_ARG_HELP_MSG)
    args = arg_parser.parse_args()
    change_license(args.path, args.license)
