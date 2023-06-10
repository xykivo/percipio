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

// Tour: https://go.dev/tour/generics/1

package main

import (
	"fmt"
	"math"
)

func InSlice[T comparable](slice []T, value T) int {
	for i, v := range(slice) {
		if v == value {
			return i
		}
	}
	return -1
}

func GenericFunc() {
	s := []int{0, 1, 2, 3, 4, 5, 6, 7}
	for _, v := range([]int{7, 8}) {
		i := InSlice(s, v)
		if -1 != i {
			fmt.Println(v, " is in ", s)
		} else {
			fmt.Println(v, " is not in ", s)
		}
	}
}

type Number interface {
	~int | ~float32 | ~float64
}

type Vector2D[T Number] struct {
	x T
	y T
}

func (vector Vector2D[T]) Length() float64 {
	return math.Sqrt(float64(vector.x * vector.x) + float64(vector.y * vector.y))
}

func GenericTypes() {
	vf32 := Vector2D[float32]{1.0, -1.0}
	fmt.Println("the length of ", vf32, " = ", vf32.Length())
	vf64 := Vector2D[float32]{-1.0, 1.0}
	fmt.Println("the length of ", vf64, " = ", vf64.Length())
}

func main() {
	fmt.Println("generics")
	GenericFunc()
	GenericTypes()
}
