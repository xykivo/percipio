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
'''Print dice rolls probablities
'''

import argparse
import collections
import re

_DICE_STRING_RE = re.compile(r'(?P<count>\d+)d(?P<die>\d+)')
_MAX_COUNT = 5
_MIN_COUNT = 1
_MAX_SIDES = 100
_MIN_SIDES = 1

_DICE_HELP_MSG = f'''The dice rolled.
Must be in form of #d#. Where the first number is the dice count, and the second is the number of die of the dice.
The dice count must be in the range [{_MIN_COUNT}, {_MAX_COUNT}].
The dice die must be in the range [{_MIN_SIDES}, {_MAX_SIDES}].
'''


class _Dice:

    @staticmethod
    def init_from_string(in_dice_str):
        dice_match = _DICE_STRING_RE.match(in_dice_str)
        if dice_match is None:
            raise ValueError(f'Invalid dice argument {in_dice_str}')
        count = int(dice_match.group('count'))
        if _MIN_COUNT > count or count > _MAX_COUNT:
            raise ValueError(
                f'Invalid dice count {count} - must be in the range [{_MIN_COUNT}, {_MAX_COUNT}]'
            )
        die = int(dice_match.group('die'))
        if _MIN_SIDES > die or count > _MAX_SIDES:
            raise ValueError(
                f'Invalid die die {die} must be in the range [{_MIN_SIDES}, {_MAX_SIDES}]'
            )
        return _Dice([die] * count)

    @staticmethod
    def combine(in_dice_list):
        combined_dice = []
        for dice in in_dice_list:
            combined_dice.extend(dice._dice)
        return _Dice(combined_dice)

    def __init__(self, in_dice):
        self._dice = in_dice

    def __str__(self):
        return ' '.join([
            f'{count}d{dice}'
            for dice, count in collections.Counter(self._dice).items()
        ])

    def print_odds(self):
        print(f'Rolling {self}')
        results = []
        self._roll_dice(len(self._dice) - 1, 0, results)
        counted_results = collections.Counter(results)
        for roll, roll_count in sorted(counted_results.items(),
                                       key=lambda item: item[0]):
            print(
                f'{roll:<8}\t{roll_count}/{len(results):<16}\t{"*" * roll_count:<128}'
            )

    def _roll_dice(self, in_die_index, in_roll_result, io_results):
        # add 1 to end range so all die are represented in roll_result
        for roll_result in range(1, self._dice[in_die_index] + 1):
            result = roll_result + in_roll_result
            if 0 == in_die_index:
                io_results.append(result)
            else:
                self._roll_dice(in_die_index - 1, result, io_results)


def _is_dice_arg(in_arg_str):
    return _Dice.init_from_string(in_arg_str)


if '__main__' == __name__:
    arg_parser = argparse.ArgumentParser(
        description='Print sice rolls probablities')
    arg_parser.add_argument('dice',
                            metavar='DICE',
                            type=_is_dice_arg,
                            nargs='+',
                            help=_DICE_HELP_MSG)
    args = arg_parser.parse_args()
    dice = _Dice.combine(args.dice)
    dice.print_odds()
