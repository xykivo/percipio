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

'''Data access and management used for neural network training, testing and
inference.
'''

import emnist
import numpy
import os

class _Emnist:
    '''Manage EMNIST training/test/inference data
    '''
    def info(self):
        '''
        '''
        if os.path.isfile(emnist.get_cached_data_path()):
            self._print_data_cache_path()
        else:
            print('EMNISt data is not cached')

    def download(self):
        '''Downkiad and cached EMNIST to the local system
        '''
        emnist.ensure_cached_data()
        self._print_data_cache_path()

    def delete(self):
        '''Delete a cached EMNIST data from the local system
        '''
        print('Deleting EMNISt data cache', emnist.get_cached_data_path())
        emnist.clear_cached_data()

    def get_labeled_training_data(self, name):
        '''Get a list of EMNIST data and labeels used for training

        :return: List of training data tuples (data, label)
        '''
        training_data, training_labels = emnist.extract_training_samples(name)
        return self._label_data(training_data, training_labels)

    def get_labeled_test_data(self, name):
        '''Get a list of EMNIST data and labeels used for testing

        :return: List of testing data tuples (data, label)
        '''
        test_data, test_labels = emnist.extract_test_samples(name)
        return self._label_data(test_data, test_labels)

    def _print_data_cache_path(self):
        '''
        '''
        print('EMNIST data is cached in:', emnist.get_cached_data_path())

    def _label_data(self, data_list, label_list):
        '''
        '''
        return [(data, label) for data, label in zip(data_list, label_list)]

class _Data:
    '''Manage training/test/inference data from various sources (backends)
    '''

    def __init__(self):
        '''Initialize the data object
        '''
        self._backend_map = {'digits': _Emnist()}

    def info(self):
        '''Print information about training/test/inference data
        '''
        for backend in self._backend_list:
            backend.info()

    def download(self):
        '''Download training/test/inference data to the local system
        '''
        for backend in self._backend_list:
            backend.download()

    def delete(self):
        '''Delete training/test/inference data from the local sysetm
        '''
        for backend in self._backend_list:
            backend.delete()

    def get_labeled_training_data(self, name):
        '''Get a list of data and labeels used for training

        The data returned is flattened to a single dimension.
        :return: List of training data tuples (data, label)
        '''
        return [(self._flatten_data(data), label) for data, label in
                self._backend_map[name].get_labeled_training_data(name)]

    def get_labeled_test_data(self, name):
        '''Get a list of data and labeels used for testing

        The data returned is flattened to a single dimension.
        :return: List of test data tuples (data, label)
        '''
        return [(self._flatten_data(data), label) for data, label in
                self._backend_map[name].get_labeled_test_data(name)]

    @property
    def _backend_list(self):
        '''Access the list of data backends

        :return: List of data backends in which each backends appears exactly
                 once
        '''
        return list(set(self._backend_map.values()))

    def _validate_data_name(self, name):
        '''Validate the given data name is supported
        '''
        if not name in self._backend_map:
            raise Exception(f'Unknown problem name {name}')

    def _flatten_data(self, data):
        '''Flatten multi dimension data to a single dimension.

        Flatten multi dimensional data to a single dimension so it can be easily
        fed into a neural network.
        If the data is one dimensional it will not be changed.
        :return: The given data flattened to a single dimension = list of values
        '''
        return numpy.reshape(data, -1)

_data = _Data()

def info():
    '''Print information about the data used for inference or training
    '''
    _data.info()

def download():
    '''Download the data used for inference or training
    '''
    _data.download()

def delete():
    '''Delete the downloaded data used for inference or training
    '''
    _data.delete()

def get_labeled_training_data(name):
    '''Get a list of data and labeels used for training

    :return: List of training data tuples (data, label)
    '''
    return _data.get_labeled_training_data(name)

def get_labeled_test_data(name):
    '''Get a list of data and labels used for testing

    :return: List of test data tuples (data, label)
    '''
    return _data.get_labeled_test_data(name)
