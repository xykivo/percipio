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
import enum
import re
import typing

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


class _DiceError(Exception):
    '''Raised when there is an error in rolling dice
    '''


class _RollType(enum.Enum):
    ADD = 0,
    ADVANTAGE = 1,
    DISADVANTAGE = 2,

    @staticmethod
    def from_flags(advantage: bool, disadvantage: bool):
        if advantage:
            return _RollType.ADVANTAGE
        elif disadvantage:
            return _RollType.DISADVANTAGE
        return _RollType.ADD


class _Dice:

    @staticmethod
    def from_string(in_dice_str: str):
        '''Create a dice object from a string description of a dice
        '''
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
    def combine(in_dice_list: typing.List[str]):
        '''Create a dice object by combining all the dice strings in the give
        dice list
        '''
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

    def print_odds(self, roll_type: _RollType):
        '''Print the odds of getting each possible result for
        '''
        print(f'Rolling {self}')
        results = []
        # start with in_roll_result of 0 because it represents the null dice
        self._roll_dice(roll_type, len(self._dice) - 1, 0, results)
        counted_results = collections.Counter(results)
        for roll, roll_count in sorted(counted_results.items(),
                                       key=lambda item: item[0]):
            print(
                f'{roll:<8}\t{float(roll_count)/float(len(results)):<5.2f}\t{roll_count}/{len(results):<8}\t{"*" * roll_count:<128}'
            )

    def _roll_dice(self, roll_type, in_die_index, in_roll_result, io_results):
        # add 1 to end range so all die are represented in roll_result
        for roll_result in range(1, self._dice[in_die_index] + 1):
            if _RollType.ADD == roll_type:
                result = roll_result + in_roll_result
            elif _RollType.ADVANTAGE == roll_type:
                result = max(roll_result, in_roll_result)
            elif _RollType.DISADVANTAGE == roll_type:
                # The null dice must be discarded in this case otherwise it
                # will alway be the min result (null_dice = 0)
                if 0 != in_roll_result:
                    result = min(roll_result, in_roll_result)
                else:
                    result = roll_result
            else:
                raise _DiceError('Error: unknown roll type')
            if 0 == in_die_index:
                io_results.append(result)
            else:
                self._roll_dice(roll_type, in_die_index - 1, result,
                                io_results)


def _dice_arg(in_arg: str):
    return _Dice.from_string(in_arg)


if '__main__' == __name__:
    arg_parser = argparse.ArgumentParser(
        description='Print sice rolls probablities')
    roll_type_group = arg_parser.add_mutually_exclusive_group()
    arg_parser.add_argument('--advantage',
                            '-a',
                            dest='advantage',
                            action='store_true',
                            default=False,
                            help='Use max die value instead of adding')
    roll_type_group.add_argument('--disadvantage',
                                 '-d',
                                 dest='disadvantage',
                                 action='store_true',
                                 default=False,
                                 help='Use min die value instead of adding')
    arg_parser.add_argument('dice',
                            metavar='DICE',
                            type=_dice_arg,
                            nargs='+',
                            help=_DICE_HELP_MSG)
    args = arg_parser.parse_args()
    dice = _Dice.combine(args.dice)
    dice.print_odds(_RollType.from_flags(args.advantage, args.disadvantage))
