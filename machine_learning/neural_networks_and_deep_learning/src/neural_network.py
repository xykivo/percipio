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

'''Various neutal networks
'''

import numpy

class FeedforwardNeuralNetwork:
    '''Feedforward neutal network that implements the stochastic gradient
    descent machine learning algorithm.

    Gradients are calculated using backpropagation.
    '''

    def __init__(self, layers_sizes):
        '''Initialize the neural network

        :param layers_sizes: The sizes of the of network layers. The 0th layer
                             is the input layer, and [-1] layers is the outpu
                             layer.
                             E.g. if the layers_sizes = [4, 3, 2], then the
                             - 0th (input) layer has 4 inputs/neurons
                             - 1st layer has 3 neurons
                             - 2nd layer has 2 outputs/neurons
        '''
        self._layers_sizes = layers_sizes
        self._weights = [numpy.random.randn(out_neuron, in_neuron) for
                         out_neuron, in_neuron in
                         zip(layers_sizes[:-1], layers_sizes[1:])]
        self._biases = [numpy.random.randn(neuron, 1)for neuron in layers_sizes]

    @property
    def layers_sizes(self):
        ''':return: A list that contains the number of neurons in each layer
        '''
        return self._layers_sizes

    @property
    def layers_count(self):
        ''':return: The number of layers in the network
        '''
        return len(self._layers_sizes)

    def infer(self, inpput):
        '''Return the network output for a given input

        :param input: The input data vector. The size (length) of this vector
                      must equal the input layer size (length).
        '''
        if len(self._layers_sizes) != len(input):
            raise Exception("Input vector size does not equal input layer size")
        data = input
        for weight, bias in zip(self._weights, self._biases):
             data = self._activation_function(numpy.dot(weight, input))
        return data

    def train(
            self,
            training_data,
            epochs,
            mini_batch_size,
            learning_rate,
            test_data=None):
        '''Use the given training data to train the network using stochastic
        gradient descent.

        :param training_data: List of tuples (input, output/label), where input
                              is a vector whose size is equal to the input layer
                              size, and output is the value (scalar or vector)
                              of the expected output.
                              This data is used to train the network.
        :param epocs: The number of epocs to run during training
        :param mini_batch_size: The size of each mini batch (= number of labeld
                                inputs) used in a mini batch
        :param learning_rate: The learning rate multiplier (= eta)
        :param test_data: List of tuples (input, output/label) where input is a
                          vector whose is the size is equal to the input layer
                          size, and output is the value of the expected output.
                          This data is used to test the quality of training.
        '''
        # TODO(xykivo@gmail.com) implement
        pass
