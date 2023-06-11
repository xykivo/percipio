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

# Chapter 1

## Sigmoid Neurons

- Sigmoid neurons simulating perceptrons, part 1:

  Show that multiplying the weights and biaases of a perceptron doesn't change
  network behaviour.

  Ther perception function is one of

  $$
  \displaystyle
  \begin{equation}
    output = \begin{cases}
      0 & w \cdot x + b \le 0 \\
      1 & w \cdot x + b > 0
    \end{cases}
  \end{equation}
  $$

  If we multipley both w, and b by c we get

  $$
  \displaystyle
  c \cdot w \cdot x + c \cdot b \rArr c \cdot (w \cdot x + b) \\
  w \cdot x + b \le 0 \rArr c \cdot (w \cdot x + b) \le 0 \\
  w \cdot x + b > 0 \rArr c \cdot (w \cdot x + b) > 0
  $$

- Sigmoid neurons simulating perceptrons, part 2:

  Let us have a perceptron neural network with a given input, where all neurons

  $$
  \displaystyle
  w \cdot x + b \ne 0
  $$

  Show that if we replace all perceptron neurons with sigmoid neurons, and
  multiply weights and biases by $c > 0$, and $c \rarr \infin$, then the
  behaviour of the sigmoid network is the same as the perceptron network.

  The sigmoid function

  $$
  \displaystyle
  \sigma(w \cdot x + b) = \frac{1}{1 + \epsilon ^ {(-w \cdot x - b)}}
  $$

  The sigmoid function where w and b are multiplied by c

  $$
  \displaystyle
  \sigma(c \cdot (w \cdot x + b)) =
    \frac{1}{1 + \epsilon ^ {(c \cdot (-w \cdot x - b))}} \\
  $$

  when $c \rarr \infin$

  $$
  \displaystyle
  c \rarr \infin \\
  \dArr \\
  \begin{equation}
    1 + \epsilon ^ {(c \cdot (-w \cdot x - b))} \rarr \begin{cases}
      0 & \text{if} & w \cdot x + b > 0 \\
      \infin & \text{if} & w \cdot x + b < 0
    \end{cases}
  \end{equation} \\
  \dArr \\
  \begin{equation}
    \frac{1}{1 + \epsilon ^ {(c \cdot (-w \cdot x - b))}} \rarr \begin{cases}
      1 & \text{if} & w \cdot x + b > 0 \\
      0 & \text{if} & w \cdot x + b < 0
    \end{cases}
  \end{equation}
  $$

## The Architecture of Neural Networks