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

# Chapter 1 - Neural Networks

## Sigmoid Neurons

### Sigmoid neurons simulating perceptrons, part 1:

Show that multiplying the weights and biaases of a perceptron doesn't change
network behaviour.

The percepton function is one of

```math
\displaylines

output = \begin{cases}
  0 & w \cdot x + b \le 0 \\
  1 & w \cdot x + b > 0
\end{cases}
```

If we multipley both w, and b by c we get

```math
c \cdot w \cdot x + c \cdot b \Rightarrow c \cdot (w \cdot x + b)
```

```math
w \cdot x + b \le 0 \Rightarrow c \cdot (w \cdot x + b) \le 0
```

```math
w \cdot x + b > 0 \Rightarrow c \cdot (w \cdot x + b) > 0
```

### Sigmoid neurons simulating perceptrons, part 2:

Let us have a perceptron neural network with a given input, where all neurons

```math
w \cdot x + b \ne 0
```

Show that if we replace all perceptron neurons with sigmoid neurons, and
multiply weights and biases by $c > 0$, and $c \rightarrow \infty$, then the
behaviour of the sigmoid network is the same as the perceptron network.

The sigmoid function

```math
\sigma(w \cdot x + b) = \frac{1}{1 + \epsilon ^ {(-w \cdot x - b)}}
```

The sigmoid function where w and b are multiplied by c

```math
\sigma(c \cdot (w \cdot x + b)) =
  \frac{1}{1 + \epsilon ^ {(c \cdot (-w \cdot x - b))}}
```

when $c \rightarrow \infty$

```math
c \rightarrow \infty \newline
```

```math
\Downarrow
```

```math
\epsilon ^ {(c \cdot (-w \cdot x - b))} \rightarrow \begin{cases}
  0 & \text{if} & w \cdot x + b > 0\\
  \infty & \text{if} & w \cdot x + b < 0
\end{cases}
```

```math
\Downarrow
```

```math
\frac{1}{1 + \epsilon ^ {(c \cdot (-w \cdot x - b))}} \rightarrow \begin{cases}
  1 & \text{if} & w \cdot x + b > 0\\
  0 & \text{if} & w \cdot x + b < 0
\end{cases}
```

## The Architecture of Neural Networks

### Generate bitwise representation from digit neurons

Let the last layer neuorons be [d0 - d9].<br/>
Let the bitwise representation output neurons be [o0 - o3].

Bitwise represntation of each digit:

```
0 = 0000
1 = 0001
2 = 0010
3 = 0011
4 = 0100
5 = 0101
6 = 0110
7 = 0111
8 = 1000
9 = 1001
```

We will show for $o_0$, simliar logic can be applied to [ $o_1$ - $o_3$ ].

$b_0$ is lit by [ $d_1$, $d_3$, $d_5$, $d_7$, $d_9$ ].

if $d_i$ is lit, it means that its $output > 0.99$, if it's not lit its
$output < 0.01$. We assume simliar outputs are required for $o_x$.

Let

```math
o_i = \sum_{j=0}^9 w_j * d_j + b_j
```

That means that for b0 the following weights and biases can to be used

```math
w_0 = 0 \cdot b_0 + 0 \\
```

```math
w_1 = 1 \cdot b_1 + 0 \\
```

```math
w_2 = 0 \cdot b_2 + 0 \\
```

```math
w_3 = 1 \cdot b_3 + 0 \\
```

```math
w_4 = 0 \cdot b_4 + 0 \\
```

```math
w_5 = 1 \cdot b_5 + 0 \\
```

```math
w_6 = 0 \cdot b_6 + 0 \\
```

```math
w_7 = 1 \cdot b_7 + 0 \\
```

```math
w_8 = 0 \cdot b_8 + 0 \\
```

```math
w_9 = 1 \cdot b_9 + 0 \\
```

This will cause $o_0$ to have a $output > 0.99$ if the digits neurons 1, 3,
5, 7, 9 are lit, and an $output < 0.01$ if these same digits are not lit.

As stated above, a simliar process can be applied to other bit outputs, each
with the set of digits in which it is lit.

## Learning with Gradient Descent

### Show that $\vert \vert v \vert \vert$ is constrained by $\epsilon$

Proof that the choice for $\Delta v$, which minimizes
$\Delta C = \nabla C \cdot \Delta v$ is $\Delta v = -\eta \cdot \nabla C$, where
$\eta = \frac{\epsilon}{\vert \vert \nabla C \vert \vert}$ is determined by the
size constraint of $\vert \vert \Delta v \vert \vert = \epsilon$.

```math
\Delta v =
  - \eta \cdot \nabla C =
  - \frac{\epsilon}{\vert \vert \nabla C \vert \vert} \nabla C
```

```math
\Downarrow
```

```math
\Delta C \approx \nabla C \cdot \Delta v =
```

```math
- \frac{\epsilon}{\vert \vert \nabla C \vert \vert} \nabla C \cdot \nabla C =
```

```math
- \frac{\epsilon}{\vert \vert \nabla C \vert \vert} \nabla C ^ 2 =
```

```math
- \frac{\epsilon}{\vert \vert \nabla C \vert \vert} \vert \vert \nabla C \vert \vert ^ 2 =
```

```math
- \epsilon \cdot \vert \vert \nabla C \vert \vert
```

```math
\Downarrow
```

```math
\nabla C \cdot \Delta v = - \epsilon \cdot \vert \vert \nabla C \vert \vert
```

From Cauchy–Schwarz inequality we get

```math
\nabla C \cdot \Delta v
\leq
\vert \vert \nabla C \vert \vert \cdot
\vert \vert \Delta v \vert \vert
```

```math
\Downarrow
```

```math
- \epsilon \cdot \vert \vert \nabla C \vert \vert
\leq
\vert \vert \nabla C \vert \vert \cdot
\vert \vert \Delta v \vert \vert
```

```math
\Downarrow
```

```math
\epsilon \cdot \vert \vert \nabla C \vert \vert
\geq
\vert \vert \nabla C \vert \vert \cdot
\vert \vert \Delta v \vert \vert
```

```math
\Downarrow
```

```math
\epsilon \geq \vert \vert \Delta v \vert \vert
```

### What happens when $C$ is a 1 dimension function?

The geometric representation of gradient descent in the 1 dimensional case is
finding the minimum of a function.

### Advantage and disadvantage of mini batch size is 1 in stochastic learning?

The main advantage of using a mini batch size of 1 (online learning), is that
the learning can be performed on data that is not known in advance. Each time
new input data is provided learning can be done, as long as there is a data
label. This is useful for using machine learning in systems that get continous
input, such as spam filter.

The disadvantage of online learning is that each incoming input has a larger
impact, and can cause the gradient descent to have greater variation, causing
the learning to take more time.

### Write the equation $a_{i+1} = \sigma(a_i \cdot w_i + b_i)$ in component form

$$ \newline
\sigma(a_{i+1}) = \frac{1}{1 + \sum_j w_{ij}a_{ij} + b_{ij}}
$$

# Chapter 2 - Backpropagation

## The 4 Backpropagation Equations

### Alternate presentation of the backpropagation equations

Show that BP1 $\delta^L = \nabla_a C \odot \sigma'(z^L)$ can be written as
$\delta^L = \sum'{(z^L)}\nabla_aC$ where $\sum{'(z^L)}$ is a square matrix whose
diagonal values are $\sigma'(z^L_j)$, and whose non diagonal values is $0$.

$\delta^L = \nabla_a C \odot \sigma'(z^L)$ is equivalent to
$\delta^L_j = \frac{\partial C}{\partial a^L_j} \sigma'(z^L_j)$

Proof:

By definition (D0)
$$
\nabla_aC = (\frac{\partial C}{\partial a_0}, \frac{\partial C}{\partial a_1},
..., \frac{\partial C}{\partial a_n}) \newline
$$

By definition (D1)
$$
\sum{'(z^L)} =
\begin{pmatrix}
\sigma'(z^L_0) & 0 & ... & 0 \\
0 & \sigma'(z^L_1) & ... & 0 \\
... & ... & ... & ... \\
0 & 0 & ... & \sigma'(z^L_n)
\end{pmatrix}
$$

From D0 and D1 we get (E0)

$$
\sum{'(z^L)} \cdot \nabla_aC =

\begin{pmatrix}
\sigma'(z^L_0) & 0 & ... & 0 \\
0 & \sigma'(z^L_1) & ... & 0 \\
... & ... & ... & ... \\
0 & 0 & ... & \sigma'(z^L_n)
\end{pmatrix}

\cdot

\begin{pmatrix}
\frac{\partial C}{\partial a_0} \\
\frac{\partial C}{\partial a_1} \\
... \\
\frac{\partial C}{\partial a_n}
\end{pmatrix}

=
\sum_j{\sigma'(z^L_j)} \cdot \frac{\partial C}{\partial a_j}
$$
