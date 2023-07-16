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

'''Main entry point to the neural network example

Currently this example supports the following machine learning problems:
- Digit image classification
'''

import pkg_resources

INSTALLED_PACKAGES = set(package.key for package in pkg_resources.working_set)
REQUIRED_PACKAGES = set(['numpy', 'python-mnist'])
missing_packages = REQUIRED_PACKAGES - INSTALLED_PACKAGES
if 0 < len(missing_packages):
    print('Error: missing the follwing Python pakcages', missing_packages)
    print('  Can be installed via pip3: pip3 install', ' '.join(missing_packages))
    exit(1)

import argparse

PROBLEM_LIST = ['digit_classification']
PROBLEM_HELP_MSG = 'The problem solved, must be one of [{0}]'.format(
    ', '.join(PROBLEM_LIST))

if '__main__' == __name__:
    arg_parser = argparse.ArgumentParser(
            description=__doc__,
            formatter_class=argparse.RawDescriptionHelpFormatter)
    arg_parser.add_argument('problem', metavar='PROBLEM', choices=PROBLEM_LIST,
                            help=PROBLEM_HELP_MSG)
    arg_parser.parse_args()
    exit(0)
