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

'''Generate host run files for C++ Python targets in C++ build tools package.

This script will build the C++ build tools package in the host configuration
and copy the generated files to the host configuration.

This is a workaround to a bug in Bazel, where the Python targets run files
are not generated in the host configuration.
See https://github.com/bazelbuild/bazel/issues/11279.

This script assumes that bazel is in the system path.
'''

import argparse
import os
import shutil
import subprocess


def git_repo_root(path):
    '''Find the Git repository root directory

    :param path: Absolute path of the script under a git repository
    '''
    if '.git' in os.listdir(path):
        return path
    head, tail = os.path.split(path)
    if (tail is None) or ('' == tail):
        raise Exception('Script must be located inside a git repository')
    return git_repo_root(head)


if '__main__' == __name__:
    arg_parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    args = arg_parser.parse_args()
    repo_root = git_repo_root(os.path.abspath(os.path.dirname(__file__)))
    config_out_sub_dir = os.path.join('bin', 'build_tools', 'cc')
    host_config_out_dir = os.path.join(
        repo_root, 'bazel-out', 'host', config_out_sub_dir)
    opt_config_out_dir = os.path.join(
        repo_root, 'bazel-out', 'k8-opt', config_out_sub_dir)
    os.makedirs(host_config_out_dir, exist_ok=True)
    for tool in ['clang-format', 'clang-tidy']:
        runfiles_dir = tool + '.runfiles'
        dst_runfiles = os.path.join(host_config_out_dir, runfiles_dir)
        build_clang_format = subprocess.run(
            ['bazel', 'build', '-c', 'opt', '//build_tools/cc:' + tool])
        if 0 != build_clang_format.returncode:
            raise Exception('Failed to build {0} build tool'.format(tool))
        shutil.copytree(
            os.path.join(opt_config_out_dir, runfiles_dir),
            dst_runfiles,
            dirs_exist_ok=True)
    exit(0)
