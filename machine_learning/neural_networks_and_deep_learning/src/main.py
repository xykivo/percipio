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
REQUIRED_PACKAGES = set(['numpy', 'emnist'])
missing_packages = REQUIRED_PACKAGES - INSTALLED_PACKAGES
if 0 < len(missing_packages):
    print('Error: missing the follwing Python pakcages:',
          ', '.join(missing_packages))
    print('  Can be installed via pip3: pip3 install', ' '.join(missing_packages))
    exit(1)
DIGIT_IMAGE_SIZE = 28 * 28
NETWORK_SIZES = {
    'digit_classification': [DIGIT_IMAGE_SIZE, 32, 10]
}

import argparse

import data
import neural_network

PROBLEM_DATA_MAP = {'digit_classification' : 'digits'}
PROBLEM_LIST = PROBLEM_DATA_MAP.keys()
PROBLEM_HELP_MSG = 'The problem solved, must be one of [{0}]'.format(
    ', '.join(PROBLEM_LIST))

def add_data_subparser(arg_subparsers):
    '''Add an argument sub parser for data management command

    :param arg_subparsers: The subparser list the data command sub parwer is
                           added to
    '''
    data_subparser = arg_subparsers.add_parser(
            'data', help='Manage training and test data')
    data_subparser.add_argument('-d', '--download',
                                action='store_true',
                                help='Download data and cache it')
    data_subparser.add_argument( '-r', '--delete',
                                action='store_true',
                                help='Delete data cache')

def data_cmd_handler(args):
    '''Manage training and test data
    '''
    if args.download:
        data.download()
    elif args.delete:
        data.delete()
    else:
        data.info()

def add_train_subparser(arg_subparsers):
    '''Add an argument sub parser for the train command

    :param arg_subparsers: The subparser list the train command sub parwer is
                           added to
    '''
    train_sbuparser = arg_subparsers.add_parser(
            'train', help='Train a neural network to solve the given problem')
    train_sbuparser.add_argument('problem', metavar='PROBLEM',
                                 choices=PROBLEM_LIST,
                                 help=PROBLEM_HELP_MSG)
    train_sbuparser.add_argument(
            '--epochs', metavar='EPOCHS', default=32, type=int,
            help='The number of epochs to run during training (int).')
    train_sbuparser.add_argument(
            '--mini-batch-size',
            metavar='MINI_BATCH_SIZE', dest='mini_batch_size',
            default=8, type=int,
            help='The size of a mini batch in training (int).')
    train_sbuparser.add_argument(
            '--training-rate',
            metavar='TRAINING_RATE', dest='learning_rate',
            default=3.0, type=float,
            help='The learning rate multiplier - eta (float).')

def train_cmd_handler(args):
    '''Train a network to solve a given problem
    '''
    neural_net = neural_network.FeedforwardNeuralNetwork(
            NETWORK_SIZES[args.problem])
    print('Training to solve', args.problem)
    print('  epocs =', args.epochs)
    print('  mini batch size =', args.mini_batch_size)
    print('  learning rate (eta) =', args.learning_rate)
    neural_net.train(
            data.get_labeled_training_data(PROBLEM_DATA_MAP[args.problem]),
            args.epochs,
            args.mini_batch_size,
            args.learning_rate,
            data.get_labeled_test_data(PROBLEM_DATA_MAP[args.problem]))

if '__main__' == __name__:
    arg_parser = argparse.ArgumentParser(
            description=__doc__,
            formatter_class=argparse.RawDescriptionHelpFormatter)
    arg_subparsers = arg_parser.add_subparsers(dest='command')
    add_data_subparser(arg_subparsers)
    add_train_subparser(arg_subparsers)
    args = arg_parser.parse_args()
    if 'data' == args.command:
        data_cmd_handler(args)
    elif 'train' == args.command:
        train_cmd_handler(args)
    exit(0)
