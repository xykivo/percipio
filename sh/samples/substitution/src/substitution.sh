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
echo "command substitution"
echo "====================================================================="

echo "command substitution"

date=`date`
echo "date = $date"

uptime=`date ; uptime`
echo "uptime = $uptime"

whoami=`whoami`
echo "whoami = $whoami"

netstat=`netstat`
echo "netstat=$netstat"

echo "\n====================================================================="
echo "variable substitution"
echo "====================================================================="

var="variable-0"
echo "regular substitution var=${var:-var-is-not-set}"

echo "variable substitution when variable is set var=${var:-var-is-not-set}"
unset var
echo "variable substitution when variable is not set var=${var:-var-is-not-set}"

echo "variable substitution when variable is not set var=${var:=setting-var}"
echo "variable substitution when variable is set var=${var:=var-is-not-set}"

replacement="variable-replacement"
unset var
echo "variable substitution it's not set var=${var:+$replacement}"
var="variable-1"
echo "variable substitution when it's set var=${var:+$replacement}"

unset var
msg="write message to stderr because var is not set"
echo "variable substitution when variable is not set var=${var:?$msg}"
