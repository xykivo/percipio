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

// Tour: https://go.dev/tour/flowcontrol/8

package main

import (
	"fmt"
	"math"
)

func compare(a, b, tolerance float64) bool {
	if diff := math.Abs(a - b) ; diff < tolerance {
		return false
	}
	return true
}

func sqrt(x float64) float64 {
	c := 0
	z := 1.0
	for compare(z * z, x, 0.05) {
		z -= (z * z - x) / (2 * z)
		c = c + 1
		if (111 < c) {
			panic("Failed to find sqrt after more than 111 attempts")
		}
	}
	return z
}

func main() {
	fmt.Println("loop - calc sqrt")
	floats := []float64 {7, 64, 16, 512, 121}
	for _, f := range(floats) {
		fmt.Println("sqrt(", f, ") =", sqrt(f))
	}
}
