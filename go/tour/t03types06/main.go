// BSD 3-Clause License
//
// Copyright (c) 2023, Dror Smolarsky
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

// Tour: https://go.dev/tour/moretypes/6

package main

import (
	"fmt"
	"strings"
)

func intArray() [10]int {
	var a [10]int
	f0 := 1
	f1 := 1
	for i := 0 ; len(a) > i ; i++ {
		a[i] = f1
		f1 = f0 + f1
		f0 = a[i]
	}
	return a
}

func makeSlices() {
	letters := []string{"x", "y", "z", "w"}
	fmt.Println("slice from array literal", letters)
	integers := make([]int, 5, 10)
	fmt.Println("slice from make", integers, "len=", len(integers), "cap=", cap(integers))
}

func intSlices(sliceSize int) {
	a := intArray()
	if len(a) < sliceSize {
		fmt.Println("slice", a[0 : len(a) - 1])
	} else {
		for i := 0 ; len(a) > (i + sliceSize) ; i++ {
			s := a[i : i + sliceSize]
			fmt.Println(strings.Repeat(" ", i), "slice", s)
		}
	}
}

func slicesAreReferences() {
	a := intArray()
	s0 := a[:]
	s1 := a[1:len(a) / 2]
	fmt.Println(s0, s1)
	s1[0] = 0
	fmt.Println(s0, s1)
}

func nilSlice() {
	var s []int
	fmt.Println("nil slice", s, len(s), cap(s))
}

func sliceOfSlices() {
	ticTacToe := [][]string{
		[]string{"-", "-", "-"},
		[]string{"-", "-", "-"},
		[]string{"-", "-", "-"},
	}
	ticTacToe[0][1] = "X"
	ticTacToe[1][1] = "O"
	ticTacToe[2][2] = "X"
	fmt.Println("slice of slices", ticTacToe)
}

func appendToSlice() {
	s := make([]int, 5)
	s = append(s, 1)
	fmt.Println("append to slice", s)
}

func rangeLoop() {
	s := make([]int, 5)
	for i := range s {
		s[i] = i
	}
	for i, v := range s {
		s[i] = i + v
	}
	fmt.Println(s)
}

func main() {
	fmt.Println("arrays & slices")
	fmt.Println(intArray())
	makeSlices()
	intSlices(100)
	intSlices(2)
	intSlices(3)
	slicesAreReferences()
	nilSlice()
	sliceOfSlices()
	appendToSlice()
	rangeLoop()
}
