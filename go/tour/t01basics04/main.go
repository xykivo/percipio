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

// Tour: https://go.dev/tour/basics/4

package main

import (
	"fmt"
	"strings"
)

func add(x int, y int) int {
	return x + y
}

func sub(x, y int) int {
	return x - y
}

func swap(a, b string) (string, string) {
	return b, a
}

func splitTime(time string) (hours, minutes string) {
	hours, minutes, ok := strings.Cut(time, ":")
	if !ok {
		panic("Invalid time format")
	}
	// Naked return, should not be used normally due to readability issues
	return
}

func main() {
	fmt.Println(swap("functions", "hello"))
	a := 42
	b := 13
	fmt.Println(a, "+", b, "=", add(a, b))
	fmt.Println(a, "-", b, "=", sub(a, b))
	t := "11:11"
	h, m := splitTime("11:11")
	fmt.Println(t, "=", h, "houws", m, "minutes")
}
