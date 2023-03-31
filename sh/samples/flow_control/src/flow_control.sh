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
echo "if-fi"
echo "====================================================================="

x=1
if [ $x -eq $x ]
then
  echo "$x = $x"
else
  echo "$x != $x"
fi

y=2
if [ $x -eq $y ]
then
  echo "$x = $y"
else
  echo "$x != $y"
fi

echo "\n====================================================================="
echo "case-esac"
echo "====================================================================="

case $x in
  1) echo "x=1"
  ;;
  2) echo "x=2"
  ;;
  3) echo "x=3"
  ;;
esac

some_string="bar"
case $some_string in
  "foo") echo "foo"
  ;;
  "bar") echo "bar"
  ;;
  "yam") echo "yam"
  ;;
esac

echo "\n====================================================================="
echo "while"
echo "====================================================================="

echo "print fibonachi series"
readonly MAX_I=5
readonly MAX_J=34

i=1
while [ $i -lt $MAX_I ]
do
  prev_j=$i
  j=$i
  while [ $j -lt $MAX_J ]
    do
      printf " $j"
      t=$j
      j=`expr $prev_j + $j`
      prev_j=$t
    done
    printf "\n"
    i=`expr $i + 1`
done

echo "\n====================================================================="
echo "for"
echo "====================================================================="

echo "print a list of string"
for s in "zero" "one" "two" "three" "four"
do
  printf " $s"
done
echo
echo

echo "print all .* files in user home directory (= primitive ls)"
for c in $HOME/.*
do
  echo "  $c"
done
echo

echo "\n====================================================================="
echo "until"
echo "====================================================================="

echo "count down from $MAX_I"
i=$MAX_I
until [ $i -eq 0 ]
do
  printf " $i"
  i=`expr $i - 1`
done
echo
echo

echo "\n====================================================================="
echo "select"
echo "====================================================================="

echo "select day of the week"
select d in monday tuesday wednesday thursday friday saturday sunday exit
do
  case $d in
    monday) echo "monday";;
    tuesday) echo "tuesday";;
    wednesday) echo "wednesday";;
    thursday) echo "thursday";;
    friday) echo "friady";;
    saturday) echo "saturday";;
    sunday) echo "sunday";;
    exit) exit;;
  esac
done
