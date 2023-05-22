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

// Tour: https://go.dev/tour/methods/9

package main

import (
	"fmt"
	"math"
)

type Vector interface {
	Length() float64;
}

type Vector3D struct {
	X float64
	Y float64
	Z float64
}

func (v *Vector3D) Length() float64 {
	if nil == v {
		return 0
	}
 	return math.Sqrt((v.X * v.X) + (v.Y * v.Y) + (v.Z * v.Z))
}

func (v *Vector3D) Negate() {
	v.X = -v.X
	v.Y = -v.Y
	v.Z = -v.Z
}

// The empty interface is an interface to all types
func PrintInterface(i interface{}) {
	fmt.Printf("print interface %v %T\n", i, i)
}

func main() {
	fmt.Println("interfaces")
	v3 := Vector3D{2, 2, 2}
	var v Vector = &v3
	fmt.Println("interface method - length of", v, "is", v.Length())
	var nv3 *Vector3D = nil
	var nv Vector = nv3
	fmt.Println("nil interface method - length of", nv, "is", nv.Length())
	PrintInterface(v)
	PrintInterface(nv)
	i := 42
	PrintInterface(i)
	s := "hello"
	PrintInterface(s)
}
