# BSD 3-Clause License
#
# Copyright (c) 2025, Dror Smolarsky
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

import argparse
import random

VOWEL_LIST = ['a', 'e', 'i', 'o', 'u', 'y']
CONSONANT_LIST = [
    'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's',
    't', 'v', 'w', 'x', 'z'
]


def _is_valid_name_count(in_name_count):
    try:
        name_count = int(in_name_count)
        if (0 < name_count) and (name_count < 17):
            return name_count
        else:
            raise argparse.ArgumentTypeError(
                f'"{in_name_count}" must be greater than 0, and less than 17')
    except ValueError as value_error:
        raise argparse.ArgumentTypeError(
            f'"{in_name_count}" is not a positive integer\n({str(value_error)})'
        )


def _generate_syllable():
    syllable_length = random.choice([1, 2, 2, 2, 3])
    if 1 == syllable_length:
        return random.choice(VOWEL_LIST)
    syllable = ''
    for i in range(syllable_length):
        if 0 == i % 2:
            syllable += random.choice(CONSONANT_LIST)
        else:
            syllable += random.choice(VOWEL_LIST)
    return syllable


def _generate_name_list(in_name_count):
    name_list = []
    while len(name_list) < in_name_count:
        syllable_count = random.choice([2, 3, 4, 4, 5, 5])
        name = ''
        for i in range(syllable_count):
            name += _generate_syllable()
        name_list.append(name)
    return name_list


if '__main__' == __name__:
    arg_parser = argparse.ArgumentParser(description='Generate random names')
    arg_parser.add_argument('name_count',
                            type=_is_valid_name_count,
                            metavar='NAME_COUNT',
                            help='Number of names genrated')
    args = arg_parser.parse_args()
    random.seed()
    name_list = _generate_name_list(args.name_count)
    print('name list:')
    for name in name_list:
        print(' ', name)
