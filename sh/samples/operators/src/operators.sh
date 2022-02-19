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

echo "\n====================================================================="
echo "arithmetic operatos"
echo "====================================================================="

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

echo "\n====================================================================="
echo "comparison operatos"
echo "====================================================================="

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

echo "\n====================================================================="
echo "boolean operators"
echo "====================================================================="

# or
if [ $x -lt $y -o $x -eq $y ]
then
    echo "-o $x < $y || $x == $y is true"
else
    echo "-o $x < $y || $x == $y is false"
fi

# and
if [ $x -gt $y -a $x -eq $x ]
then
    echo "-a $x > $y && $x == $x is true"
else
    echo "-a $x > $y && $x == $x is false"
fi

# not
if [ ! $x -lt $y ]
then
    echo "! $x < $y is true"
else
    echo "! $x > $y is false"
fi

echo "\n====================================================================="
echo "string operators"
echo "====================================================================="

s0="string-0"
s1="not-string-0"

if [ $s0 = $s1 ]
then
    echo "$s0 = $s1 is true"
else
    echo "$s0 = $s1 is false"
fi

if [ $s0 != $s1 ]
then
    echo "$s0 != $s1 is true"
else
    echo "$s0 != $s1 is false"
fi

se=""

if [ -z $se ]
then
    echo "-z \"$se\" size = 0"
else
    echo "-z \"$se\" size != 0"
fi

if [ -z $s0 ]
then
    echo "-z \"$s0\" size = 0"
else
    echo "-z \"$s0\" size != 0"
fi

if [ -n $se ]
then
    echo "-n \"$se\" size != 0 (why is -n $se size not equal 0?)"
else
    echo "-n \"$se\" size = 0"
fi

if [ -n $s0 ]
then
    echo "-n \"$s0\" size != 0"
else
    echo "-n \"$s0\" size = 0"
fi

if [ $se ]
then
    echo "-n \"$se\" is not the empty string"
else
    echo "-n \"$se\" is the empty string"
fi

if [ $s0 ]
then
    echo "-n \"$s0\" is not the empty string"
else
    echo "-n \"$s0\" is the empty string"
fi


echo "\n====================================================================="
echo "file operators"
echo "====================================================================="

if [ -e $0 ]
then
    echo "-e $0 exists"
else
    echo "-e $0 does not exist"
fi

if [ -s $0 ]
then
    echo "-s $0 file size > 0"
else
    echo "-s $0 file size == 0"
fi

if [ -d $0 ]
then
    echo "-d $0 is a directory"
else
    echo "-d $0 is not a directory"
fi

if [ -f $0 ]
then
    echo "-f $0 is a file"
else
    echo "-f $0 is not a file"
fi

if [ -p $0 ]
then
    echo "-p $0 is a named pipe"
else
    echo "-p $0 is not a named pipe"
fi

if [ -t $0 ]
then
    echo "-t $0 file descriptor is open"
else
    echo "-p $0 file descriptor is not open"
fi

if [ -t $0 ]
then
    echo "-t $0 file descriptor is open"
else
    echo "-p $0 file descriptor is not open"
fi

if [ -r $0 ]
then
    echo "-r $0 is readable"
else
    echo "-r $0 is not readable"
fi

if [ -w $0 ]
then
    echo "-w $0 is writeable"
else
    echo "-w $0 is not writeable"
fi

if [ -u $0 ]
then
    echo "-u $0 has user id bit set"
else
    echo "-u $0 does not have user id bit set"
fi

if [ -g $0 ]
then
    echo "-g $0 has group id bit set"
else
    echo "-g $0 does not have group user id bit set"
fi
