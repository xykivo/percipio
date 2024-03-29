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

# Local constants and variables
THIS_IS_A_CONSTANT="Constant"
readonly THIS_IS_A_CONSTANT
echo "Constant=$THIS_IS_A_CONSTANT"

variable="variable-0"
echo "variable="$variable
variable="variable-1"
echo "variable=$variable"
unset variable
echo $variable

# special variables
echo "script file name (argument 0) \$0=$0"
echo "[\$1, \$n] script arguments \$1=$1 \$2=$2"
echo "number of arguments \$#=$#"
echo "all arguments \$*=$*"
echo "all arguments \$@=$@"
echo "exit status of last command \$?=$?"
echo "process number of current shell \$\$=$$"
echo "process number of last background command \$!=$!"

# arrays
array_a[0]="array_a[0]"
array_a[1]="array_a[1]"
array_a[2]="array_a[2]"
array_a[3]="array_a[3]"
array_a[4]="array_a[4]"
echo "all array elements \${array_a[*]}=${array_a[*]}"
echo "all array elements \${array_a[@]}=${array_a[@]}"

array_b=("array_b[0]" "array_b[1]" "array_b[2]" "array_b[3]" "array_b[4]")
echo "all array elements \${array_b[*]}=${array_b[*]}"
echo "all array elements \${array_b[@]}=${array_b[@]}"
