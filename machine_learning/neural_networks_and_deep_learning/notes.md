# License

BSD 3-Clause License

Copyright (c) 2020-2021, Dror Smolarsky
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

# General

Notes and references for the book -
[Neural Networks and Deep Learning](http://neuralnetworksanddeeplearning.com/)

Book source code and data [repository](https://github.com/mnielsen/neural-networks-and-deep-learning.git).

# Chapter 1

## Activation Functions

For various activation functions see:

- Wikipedia: https://en.wikipedia.org/wiki/Activation_function
- DeepAI: https://deepai.org/machine-learning-glossary-and-terms/activation-function

### ReLU - Rectified Linear Unit

One of the more common activation functions used in neural networks.

```math
\displaystyle
f(x) = max(0, x)
```

The derivative is:

```math
\displaystyle
\begin{equation}
   \frac{d f(x)}{dx} = \begin{cases}
      1 & \text{if x > 0} \\
      0 & \text{if x < 0} \\
      undefined & \text{otherwise}
   \end{cases}
\end{equation}
```

## Neural Network Types

### Feedforward Neural Network

Connections between the nodes do not form circles.

https://en.wikipedia.org/wiki/Feedforward_neural_network

### Recurrent Neural Network

Connections between nodes can form circles.

https://en.wikipedia.org/wiki/Recurrent_neural_network

### Recursive Neural Network

Apply the same set of weights recursively over a structured input.

https://en.wikipedia.org/wiki/Recursive_neural_network

## Learning with Gradient Descent

Cost function (sometimes called loss or objective function). In many cases it
is the quadratice cost function = mean squared error (MSE) function.

```math
C(w, b) \equiv \frac{1}{2n} \sum{\vert \vert y(x) - (w \cdot x + b)} \vert \vert
```

Where $x$ is the input vector, $y(x)$ is the expected output, and n is the
number of input samples.

$C(w, b) > 0$ and $C(w, b) \approx 0$ when $y(x) \approx w \cdot x + b$. This
means the goal of the training algorithm is to minimize $C(w, b)$.

> _Note:_ There are other types of cost functions, including variants of MSE.

The minimization of $C(w, b)$ uses the gradient descent algorithm.

The gradient vector:

```math
\nabla C \equiv (\frac{\delta C}{\delta v_0}, \frac{\delta C}{\delta v_1}, ...,
\frac{\delta C}{\delta v_n})^T
```

The descent vector:

```math
v = (v_0, v_1, ..., v_n)^T
```

```math
\Delta v = (\Delta v_0, \Delta v_1, ..., \Delta v_n)^T
```

The change in the cost function is

```math
\Delta C \approx \nabla C \cdot \Delta v
```

If we choose $\Delta v = - \eta \cdot \nabla C$ we get

```math
\Delta C \approx - \eta \cdot \nabla C \cdot \nabla C =
  - \eta \cdot \vert \vert \nabla C \vert \vert ^2
```

For gradient descent for $C(w, b)$ we need substitute $v$ with weights $w$ and
biases $b$.

This means that $\nabla C$ has the components $\frac{\delta C}{\delta w_k}$
and $\frac{\delta C}{\delta b_l}$.

$w_k \rightarrow w'_k = w_k - \eta \frac{\delta C}{\delta w_k}$

$b_l \rightarrow b'_l = b_l - \eta \frac{\delta C}{\delta b_l}$

The cost equation (below), requires calculating the average cost of all inputs.
Thie mean calculating a quadratic equatino for each input.

```math
C(w, b) \equiv \frac{1}{2n} \sum{\vert \vert y(x) - (w \cdot x + b)} \vert \vert
```

One solution is to use stochastic gradient descent. The idea is to estimate
$\nabla C$ by computing $\nabla C_x$ for a small subset of the input chosen
randomally. By averaging a small sample (size = $m$) we can get a good estimate
of the true $\nabla C$.

```math
\frac{\sum_{j=1}^m \nabla C_{X_j}}{m} \approx \frac{\sum_X \nabla C_X}{m} = \nabla C,
```

```math
\Downarrow
```

```math
\nabla C \approx \frac{1}{m} \sum_{j=1}^m \nabla C_{X_j},
```

When we apply this to learning in neural networks we get

```math
w_k \rightarrow w'_k =
w_k - \frac{n}{m} \sum_j \frac{\delta C_{X_j}}{\delta w_k}
```

```math
b_l \rightarrow b'_l =
b_l - \frac{n}{m} \sum_j \frac{\delta C_{X_j}}{\delta b_l}
```

> _Note_
>
> There are various convention on how to scale the cost function. In the
> equations above the cost function is scaled by a factor of 1/n, where n is the
> number of samples. However in some cases the the factor of 1/n is omitted.
> This is useful when the total number of training examples isn't known in
> advance.
>
> Conceptually this makes little difference, since all it means is scaling the
> cost function by n.

An [epoch](https://deepai.org/machine-learning-glossary-and-terms/epoch) is 1
cycle of training - going through the full training dataset.
An epoch is diviided into batches. In each batch a differet subset of the
training data is fed to the network. Iterations is the number of batches needed
to complte one epoch.

# Implementing Digit Classification Network

When implementing a neural network to claisify digit images, we will use part of
training data as validation data.

In the implementation layer 0, is the input layer, and has no inputs.

For each layer the weights and biarses are stored in a matrices. Matrix w\[i\],
stores weights that connect layer i to layer i+1. $w[i]_{jk}$ is the weight for
the connection between the $k^{th}$ neuron in layer i, and the $j^{th}$ neuron
in layer i+1.

This means that vector of activations for layer i+1 is</br>
$a_{i+1} = \sigma(a_i \cdot w_i + b_i)$

Where w[i] is the weights matrix for layer i to layer i+1, and b is the vector
of biases for layers i to layer i+1.

# Data Sets

[MNIST data set](http://yann.lecun.com/exdb/mnist/)

Contains images of classified handwritten digits.
