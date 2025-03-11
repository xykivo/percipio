# BSD 3-Clause License
#
# Copyright (c) 2023, Dror Smolarsky
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must rlearning_ratein the above copyright notice,
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

import datetime
import numpy
import random

import activation_functions

class FeedforwardNeuralNetwork:
    '''Feedforward neutal network that implements the stochastic gradient
    descent machine learning algorithm.

    Gradients are calculated using backpropagation.
    '''

    def __init__(self, layers_sizes):
        '''Initialize the neural network

        :param layers_sizes: The sizes of the of network layers. The 0th layer
                             is the data layer, and [-1] layers is the outpu
                             layer.
                             E.g. if the layers_sizes = [4, 3, 2], then the
                             - 0th (input data) layer has 4 data/neurons
                             - 1st layer has 3 neurons
                             - 2nd (output) layer has 2 neurons
        '''
        self._layers_sizes = layers_sizes
        self._weights = [numpy.random.randn(in_neuron, out_neuron) for
                         out_neuron, in_neuron in
                         zip(layers_sizes[:-1], layers_sizes[1:])]
        self._biases = [numpy.random.randn(neuron)
                        for neuron in layers_sizes[1:]]
        # TODO(xykivo@gmail.com) The activation function shoul be passed as a
        #                        parameter to the __init__ function
        self._activation_function = activation_functions.Sigmoid()

        # dbg
        for layer in range(self.layers_count - 1):
            print('DBG layer', layer)
            print('DBG   weights', numpy.shape(self._weights[layer]))
            print('DBG   biases', numpy.shape(self._biases[layer]))

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

    def infer(self, input):
        '''Return the network output for a given data

        :param input: The input data vector. The size (length) of this vector
                      must equal the data layer size (length).

        '''
        output = input
        for weight, bias in zip(self._weights, self._biases):
             output = self._activation_function(numpy.dot(weight.transpose(), output) + bias)
        return output

    def train(
            self,
            training_data,
            epochs,
            mini_batch_size,
            learning_rate,
            test_data=None):
        '''Use the given training data to train the network using stochastic
        gradient descent.

        :param training_data: List of tuples (data, output/label), where data
                              is a vector whose size is equal to the data layer
                              size, and output (label) size equals the network
                              ouutput layer.
                              This data is used to train the network.
        :param epocs: The number of epocs to run during training
        :param mini_batch_size: The size of each mini batch (= number of labeld
                                data) used in a mini batch
        :param learning_rate: The learning rate multiplier (= learning_rate)
        :param test_data: List of tuples (data, output/label) where data is a
                          vector whose is the size is equal to the data layer
                          size, and output is the value of the expected output.
                          This data is used to test the quality of training.
        '''
        for epoch in range(epochs):
            random.shuffle(training_data)
            mini_batches_list = [
                    training_data[i : i + mini_batch_size]
                    for i in range(0, len(training_data), mini_batch_size)]
            for mini_batch in mini_batches_list:
                self._train_on_mini_batch(mini_batch, learning_rate)
            if test_data is not None:
                self._log(f'epoch {epoch} complete - {self._evaluate(test_data)}/{len(test_data)}')

    def _train_on_mini_batch(self, mini_batch, learning_rate):
        '''Train the network on the labeld data in the given mini batch

        Update the network weights and biases using back propogation to a single
        mini batch.
        Note that the network weights and biases are updated once per mini
        batch.

        :param mini_batch: List of tuples (data, output). where data is a
                           vector whose size is equal to the data layer size,
                           and output (label) size equal the network output
                           layer.
        :param learning rate: The learning rate multiplier (= learning_rate)
        '''
        gradient_weights = [numpy.zeros(w.shape) for w in self._weights]
        gradient_biases = [numpy.zeros(b.shape) for b in self._biases]
        for data, output in mini_batch:
            delta_gradient_weights, delta_gradient_biases =\
                    self._back_propagation(data, output)
            gradient_descent = lambda gradients, delta_gradients:\
                    [g + dg for g, dg in zip(gradients, delta_gradients)]
            gradient_weights = gradient_descent(
                    gradient_weights, delta_gradient_weights)
            gradient_biases = gradient_descent(
                    gradient_biases, delta_gradient_biases)
        update_network = lambda values, gradients:\
            [v - (learning_rate / len(mini_batch) * g)
             for v, g in zip(values, gradients)]
        self._weights = update_network(self._weights, gradient_weights)
        self._biases = update_network(self._biases, gradient_biases)

    def _back_propagation(self, input, output):
        '''Calculate the gradient descent for the cost function for the data,
        for all layers in the network for the given data and output

        :return: Tuple (delta_gradient_weights, delta_gradient_biases) where
                 gradient weights and gradient biases are lists of layers with
                 the same dimensions as the network weights and biases layers
                 lists.
        :param data: The network input - a vector of values with the same size
                     as the network 0'th layer
        :param output: The network (expected) output
        '''
        # Infer (feed forward) - calculate activated layers values
        activation = input # The current layer activation values
        activations = [activation] # list of activation values stored layer by layer
        values = [] # list of network pre activation values stored layer by layer
        for weights, biases in zip(self._weights, self._biases):
            layer_values = numpy.dot(weights, activation) + biases

            # dbg
            print('DBG', len(values),
                  'shape(weights)=', numpy.shape(weights),
                  'shape(activation)=', numpy.shape(activation),
                  'shape(layer)=', numpy.shape(layer_values))

            values.append(layer_values)
            activation = self._activation_function(layer)
            activations.append(activation)

        # dbg
        # for l, a in zip(layers, activations):
        #     print('DBG shape(layer)=', numpy.shape(l), 'shape(activation)=', numpy.shape(a))

        # Update the network using gradient descent.
        # The update happens from the last layer to the first layer.
        delta_gradient_weights = [numpy.zeros(w.shape) for w in self._weights]
        delta_gradient_biases = [numpy.zeros(b.shape) for b in self._biases]
        delta = self._cost_derivative(activations[-1], output) * \
                self._activation_function.derivative(layers[-1])

        # dbg
        # print('DBG shape(delta)=', numpy.shape(delta),
        #       'shape(activations[-2])', numpy.shape(activations[-2]),
        #       'len(activations)', len(activations))
        for i, a in zip(range(len(activations)), activations):
            print('DBG', i, 'shape(activation)', numpy.shape(a))
        print('DBG shape(activation[-2])', numpy.shape(activations[-2]))

        delta_gradient_weights[-1] = numpy.dot(delta, activations[-2].transpose())
        delta_gradient_biases[-1] = delta

        # for layer_index in range(-2, -self.layers_count, -1):
        #     delta = numpy.dot(self._weights[layer_index + 1].transpose(), delta) * \
        #             activation_functions.sigmoid_derivative(layers[layer_index])
        #     delta_gradient_weights =\
        #             numpy.dot(delta, activations[layer_index - 1].transpose())
        #     delta_gradient_biases = delta

        return delta_gradient_weights, delta_gradient_biases

    def _evaluate(self, test_data):
        '''Evaluate the quality of the network

        :return: The number of test data for which the network outputs the
                 correct result. The network output is the assumed to be the
                 index of the neuron with the highest activation value in the
                 output (final) layer.
        '''
        test_result = [(numpy.argmax(self.infer(data)), output)
                        for data, output in test_data]
        return sum(int(output == label) for (output, label) in test_result)

    def _cost_derivative(self, output_activations, expected_activations):
        '''Calculate the partial derivative of the cost of a given input that
        resulted in a a vector of activation compared to the expected result
        (label).

        :return: A vector of parital derivatives of cost(input) / activation
        '''
        return (output_activations - expected_activations)

    def _log(self, msg):
        '''Log a message to standard output

        :param meg: The message/text logged
        '''
        # TODO(xykivo@gmail.com) check verbosity
        # TODO(xykivo@gmail.com) log to file and/or standard output based on
        #                        options passed from command line
        print(f'FeedforwardNeuralNetwork [{datetime.datetime.now()}]', msg)

# 052-299-33387
# - Ask if this is her father's last will
# - There is some potential legal ambiguity about the contract Tamari and her father
#   signed. Depends on when the contract was signed before/after his brother's death
# - Nordia may still take the house
