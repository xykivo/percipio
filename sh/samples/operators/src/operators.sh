#!/bin/sh
# -*- coding: utf-8 -*-

# BSD 3-Clause License
#
# Copyright (c) 2022, Dror Smolarsky
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

echo "arithmetic operatos"

x=5
y=2
result=`expr $x + $y`
echo "$x + $y = $result"
result=`expr $x - $y`
echo "$x - $y = $result"
result=`expr $x \* $y`
echo "$x * $y = $result"
result=`expr $x / $y`
echo "$x / $y = $result"

echo "comparison operatos"

if [ $x -eq $y ]
then
    echo "-eq $x == $y is true"
else
    echo "-eq $x == $y is false"
fi

if [ $x -ne $y ]
then
    echo "-ne $x != $y is true"
else
    echo "-ne $x != $y is false"
fi

if [ $x -gt $y ]
then
    echo "-gt $x > $y is true"
else
    echo "-gt $x > $y is false"
fi

if [ $x -lt $y ]
then
    echo "-lt $x < $y is true"
else
    echo "-lt $x < $y is false"
fi

if [ $x -ge $y ]
then
    echo "-ge $x >= $y is true"
else
    echo "-ge $x >= $y is false"
fi

if [ $x -le $y ]
then
    echo "-le $x <= $y is true"
else
    echo "-le $x <= $y is false"
fi
