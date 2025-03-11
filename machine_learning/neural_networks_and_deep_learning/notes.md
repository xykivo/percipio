# License

BSD 3-Clause License

Copyright (c) 2023, Dror Smolarsky
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
\nabla C \equiv (\frac{\partial C}{\partial v_0}, \frac{\partial C}{\partial v_1}, ...,
\frac{\partial C}{\partial v_n})^T
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

This means that $\nabla C$ has the components $\frac{\partial C}{\partial w_k}$
and $\frac{\partial C}{\partial b_l}$.

$w_k \rightarrow w'_k = w_k - \eta \frac{\partial C}{\partial w_k}$

$b_l \rightarrow b'_l = b_l - \eta \frac{\partial C}{\partial b_l}$

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

# Chapter 2 - Backpropagation

## Fast Matrix Based Math

This chapter describes the math behind back propagation.

$w^l_{jk}$ denotes the weight for the connection between the $k^{th}$ neuron in
the $(l-1)^{th}$ layer to $j^{th}$ neuron in the $l^{th}$ layer.

$b^l_j$ denotes the bias for the $j^{th}$ neuron in the $l^{th}$ layer.

The activation of $a^l_j$ neuron ($j^{th}$ neuron in the $l^{th}$ layer) is:

$a^l_j = \sigma(\sum{w^l_{jk} a^{l-1}_k + b^l_j})$

The weight matrix $w^l$ is the input weights for the $l^{th}$ layer. The value
in the $j^{th}$ row and $k^{th}$ column is $w^l_{jk}$.

The bias vector $b^l$ is the input biases for the $l^{th}$ layer. The $j^{th}$
value in the vector is $b^l_j$.

The weighted input (z's) to the $l^{th}$ layer,
$z^l$ is: $z^l = w^l a^{l-1} + b^l$. Note that
$z^l_j = \sum{w^l_{jk} a^{l-1}_k + b^l_j}$.

The activation vector $a^l$ is the activation values in the $l^{th}$ layer. The
$j^{th}$ value in the vector is $a^l_j$.

The vector form of $\sigma$ (the activation functions) is
$\sigma([x, y]) = [\sigma(x), \sigma(y)]$

The vectorized form of the activation function above is:
$a^l = \sigma(z^l) = \sigma(w^l a^{l-1} + b^l)$

## Cost Function Assumptions

The cost function can be written as an average over individual training examples
$C = \frac{1}{n} \sum_x{C_x}$. For the quadratic cost function the cost for a
single training sample is $C_x = \frac{1}{2} ||y - a^L||$ ($y$ is the desired
output, and $a^L$ is the vector of activation outputs from the network).

The cost function can be written as a function of the (activation) outputs of
the neural network.
E.g. the quadratic cost function can be written as
$C = \frac{1}{2} ||y - a^L||$.

## The Hadamard Product

The Hadamard product (aka Schur product) is elementwise multiplication:

```math
\begin{bmatrix}
a \\
b
\end{bmatrix}
\odot
\begin{bmatrix}
c \\
d
\end{bmatrix}
=
\begin{bmatrix}
a \cdot c \\
b \cdot d
\end{bmatrix}
```

## The 4 Fundamental Backpropagation Equations

### The Error

The error is an intermediate value that is calculated during backpropagation.

$\delta^l_j$ is the error in the $j^{th}$ neuron in the $l^{th}$.

$\delta^l_j$ is used to calculate $\frac{\partial C}{\partial w}$ and
$\frac{\partial C}{\partial b}$

The error in the $j^{th}$ neuron in the $l^{th}$ can be defined as a derivative
of the intermediate value: $\delta^l_j = \frac{\partial C}{\partial z^l_j}$.

Note that a similar (better?) back propagation result can be achived by changing
the error in the activated value, so that
$\delta^l_j = \frac{\partial C}{\partial a^l_j}$

### Equations

__(BP1) Error in the output layer equation__

$\delta^L_j = \frac{\partial C}{\partial a^L_j} \sigma'(z^L_j)$

$\frac{\partial C}{\partial a^L_j}$ measures how fast the cost is changing as a
function of the $j^{th}$ output activation.
E.g. for the quadratic cost function
```math
C = \frac{1}{2}\sum_j({y_j - a^L_j})^2 \rightarrow
\frac{\partial C}{\partial a^L_j} = (a^L_j - y_j)
```
.

$\sigma'(z^L_j)$ measures how fast the activation function changes at $z^L_j$.

The matrix based form of the error in output equation is
$\delta^L = \nabla_a C \odot \sigma'(z^L)$, where $\nabla_a$ is a vector of the
partial derivatives $\frac{\partial C}{\partial a^L_j}$.
For the quadratic cost function the matrix based error in output function is
$\delta^L = (a^L - y) \odot \sigma'(z^L)$.

__(BP2) Error $\delta^l$ in terms of error $\delta^{l-1}$__

This equation moves the error from the $l + 1$ layer to $l$ layer. Called
repeately it propagates the error from the last layer to the first layer.

$\delta^l = ((w^{l+1})^T \delta^{l+1} \odot \sigma'(z^l))$

$(w^{l+1})^T$ is the transpose matrix weight matrix $w^{l+1}$ for the $l+1$
layer. The use of the transpose matrix can be thought as moving backwords from
the $l +1$ layer ot the $l$ layer.

The use of $\odot \sigma'(z^l)$ can be though of as moving the error through the
actication function.

By combining BP1 and BP2 we can calculate the error $\delta^l$ in any layer $l$
in the network. Use BP1 to calculate the error $\delta^L$ in the last layer,
then use BP2 repeatedly until we get to the layer we are interested in.

__(BP3) Equation for the rate of change in the cost as a function of change in
the biases__

$\frac{\partial C}{\partial b^l_j} = \delta^l_j$

This means that the error $\delta^l_j$ is equal to the rate of change
$\frac{\partial C}{\partial b^l_j}$.

In vector form this equation can be written as
$\frac{\partial C}{\partial b} = \delta$.

__(BP4) Equation for the rate of change in the cost as a function of change in
the weights__

$\frac{\partial C}{\partial w^l_{jk}} = a^{l-1}_k \cdot \delta^l_j$

The matrix form of this equation is
$\frac{\partial C}{\partial w} = a_{in} \cdot \delta_{out}$. Where $a_{in}$ is
the activation input to the weight $w$, and $\delta_{out}$ is the error of the
neuron output from the weight $w$.

__Insights from BP1-BP4__

Note that a consequence of BP4 is that if $a_{in}$ is small then the gradient
$\frac{\partial C}{\partial w}$ will also be small This makes the weight learn
slowly, since it won't change much during gradient descent.

When $\sigma(z^l_j)$ is close to 0 or 1, then $\sigma'(z^l_j) \rightarrow 0$,
which means that the neuron learns slowly if the activation is close to 0 or 1.
In this case it is said that the neuron is saturated, and as a result the weight
is learning slowly.

In summary if the input neuron has low activation value, or the output neuron is
saturated then the weight will learn slowly.

Note that if we use another activation function, e.g. one that whose derivative
is always positive: $\sigma' > 0$, and is never close to 0, the behvaiour would
be different. There would not be no slow down when the neuron is saturated.

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

The implementation uses backpropagation, which uses the cost derivative to
correct the network weights and biases.
[Good explanation of backpropagation](https://towardsdatascience.com/understanding-backpropagation-algorithm-7bb3aa2f95fd)
[Wikipedia backpropagation explanation](https://en.wikipedia.org/wiki/Backpropagation)

# Data Sets

[MNIST data set](http://yann.lecun.com/exdb/mnist/)

Contains images of classified handwritten digits.
