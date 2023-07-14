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

class FeedforwardNeuralNetwork:
    '''Feedforward neutal network that implements the stochastic gradient
    descent machine learning algorithm.

    Gradients are calculated using backpropagation.
    '''

    def __init__(self, layers_sizes):
        '''Initialize the neural network

        :param layers_sizes: The sizes of the of network layers. The 0'th layer
                             is the input layer, and [-1] layers is the outpu
                             layer.
        '''
        self._layers_sizes = layers_sizes

    def infer(self, input):
        '''Return the network output for a given input

        :param input: The input data vector. The size (length) of this vector
                      must equal the input layer size (length).
        '''
        if len(self._layers_sizes) != len(input):
            raise Exception("Input vector size does not equal input layer size")
        # TODO(xykivo@gmail.com) implement
        pass

    def train(
            self,
            training_data,
            epochs,
            mini_batch_size,
            learning_rate,
            test_data=None):
        '''Use the given training data to train the network using stochastic
        gradient descent.

        :param training_data: List of tuples (input, output), where input is
                              a vector whose size is equal to the input layer
                              size, and output is the value (scalar or vector)
                              of the expected output.
        :param epocs:
        '''
        # TODO(xykivo@gmail.com) implement
        pass