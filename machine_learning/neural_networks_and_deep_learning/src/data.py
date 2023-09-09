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
import random

class _Debug:
    '''Manage training/test/inference data used for debug
    '''

    def __init__(self, input_size=4, output_size=2, data_size=64):
        '''Initialize debug data

        :param input_size: The width of the data input vector.
                           Input data size must not be 0.
        :param output_size: The width of the output vector, which is also the
                            range of possible results [0, output_size).
                            If output size is 1, then the output is floating
                            point value in the range [0,.0 1.0].
                            Output data size must not be 0.
        :param data_size: The number of data points generated (inputs and
                          outpus).
                          Data size mmyst not be 0.
        '''
        if 0 >= input_size:
            raise Exception('Debug data input size must be greater than 0')
        if 0 >= output_size:
            raise Exception('Debug data output size must be greater than 0')
        self._input_size = input_size
        self._output_size = output_size
        self._data_size = data_size
        self._null_data()

    def into(self):
        '''Print information about debug data
        '''
        if self._labeled_training_data is None:
            print('Debug data is not initialized')
        else:
            print('Debug daa')

    def download(self):
        '''Initialize the debug data
        '''
        if self._labeled_training_data is None:
            self._labeled_training_data = self._init_data(self._data_size)
        if self._labeled_test_data is None:
            self._labeled_test_data = self._init_data(int(self._data_size / 4))

    def delete(self):
        '''Delete the debug data from memory
        '''
        self._null_data()

    def get_label_size(self, name):
        '''Get the number of possible label values

        :return: The number (count) of possible label values. Label values will
                 be in the range of [0, count), if count > 1.
                 If The number of possible label values is 1, then the label
                 value will be in the range [0.0, 1.0].
        :param name: Not used
        '''
        return self._output_size

    def get_labeled_training_data(self, name):
        '''Get a list of debug training data

        :return: List of training data tuples (data, label)
        :param name: Not used
        '''
        self.download()
        return self._labeled_training_data

    def get_labeled_test_data(self, name):
        '''Get a list of debug test data

        :return: List of testing data tuples (data, label)
        :param name: Not used
        '''
        self.download()
        return self._labeled_test_data

    def _null_data(self):
        '''Reset the debug data
        '''
        self._labeled_training_data = None
        self._labeled_test_data = None

    def _init_data(self, data_size):
        '''Initialize data and label it

        :return: A list of tuples (input, output), where input and outputs are
                 Numpy vectors with dimensions equal to the input/output data.
        :param data_size: The size of the data returned (number of labeled data
                     tuples)
        '''
        labeled_data_list = []
        for _ in range(0, data_size):
            data = numpy.random.rand(self._input_size)
            if 1 == self._output_size:
                label = random.random()
            else:
                label = random.randrange(self._output_size)
            labeled_data_list.append((data, label))
        return labeled_data_list

class _Emnist:
    '''Manage EMNIST training/test/inference data
    '''

    def info(self):
        '''Print information about EMNIST data
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

    def get_label_size(self, name):
        '''Get the number of possible label values

        :return: The number (count) of possible label values. Label values will
                 be in the range of [0, count), if count > 1.
                 If The number of possible label values is 1, then the label
                 value will be in the range [0.0, 1.0].
        :param name: The name of the EMNIST data
        '''
        LABELS_SIZE_MAP = {
            'digits': 10,
        }
        return LABELS_SIZE_MAP[name]

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
        '''Print the path to the EMNIST data cache
        '''
        print('EMNIST data is cached in:', emnist.get_cached_data_path())

    def _label_data(self, data_list, label_list):
        '''Label the given data with the given labels
        '''
        return [(data, label) for data, label in zip(data_list, label_list)]

class _Data:
    '''Manage training/test/inference data from various sources (backends)
    '''

    def __init__(self):
        '''Initialize the data object
        '''
        self._backend_map = {'debug': None, 'digits': _Emnist()}

    @property
    def backends(self):
        '''Access the backends map
        '''
        return self._backend_map

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
        return [(self._flatten_data(data), self._label_to_vector(name, label))
                for data, label
                in self._backend_map[name].get_labeled_training_data(name)]

    def get_labeled_test_data(self, name):
        '''Get a list of data and labeels used for testing

        The data returned is flattened to a single dimension.
        :return: List of test data tuples (data, label)
        '''
        return [(self._flatten_data(data), self._label_to_vector(name, label))
                for data, label
                in self._backend_map[name].get_labeled_test_data(name)]

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

    def _label_to_vector(self, name, label):
        '''Convert a label to a Numpy 1D vector with a size equal number of
        possible values.

        :return: The label is converted to
                 * If the data label size is 1, then the returned vector size is
                   1. The value of the vector is the provided label
                 * If the label is a discrete value in the range [b, e], then the
                   returned vector is a 1D vector with a size (width) of (b - a).
                   All vector values are 0, except for the value of (label-1)
                   which is 1.
                   Note that in this case the label value is assumed to be an
                   integer within the range [0, b + e).
        :param name: The name of the data
        :param label: The label value
        '''
        if 1 == self._backend_map[name].get_label_size(name):
            label_vec = numpy.zeros(1)
            label_vec[0] = label
        else:
            label_vec = numpy.zeros(self._backend_map[name].get_label_size(name))
            label_vec[label] = 1
        return label_vec

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
    '''Get a list of data and labels used for training

    :return: List of training data tuples (data, label), where both data and
             label are vectors.
             Data is a vector with a size equal to the input size.
             Label is a vector with a size equal to the number of possible
             results. If the possible result is a continous range, the label
             vector size is 1.
    '''
    return _data.get_labeled_training_data(name)

def get_labeled_test_data(name):
    '''Get a list of data and labels used for testing

    :return: List of test data tuples (data, label), where both data and
             label are vectors.
             Data is a vector with a size equal to the input size.
             Label is a vector with a size equal to the number of possible
             results. If the possible result is a continous range, the label
             vector size is 1.
    '''
    return _data.get_labeled_test_data(name)

def init_debug(input_size, output_size, data_size):
    '''Initialize debug data

    :param input_size: The size (width) of the debug data input
    :param output_size: The size (width) of the debug data output
    :param data_size: The debug training data size - also impacts test and
                      inference data size
    '''
    _data.backends['debug'] = _Debug(input_size, output_size, data_size)
