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

// Tour: https://go.dev/tour/methods/15

package main

import "fmt"

type Interface interface {
	Foo() string
}

type ImplA struct {}

func (a ImplA) Foo() string {
	return "foo-a"
}

type ImplB struct {}

func (b ImplB) Foo() string {
	return "foo-b"
}

func InterfaceTypes() {
	var i Interface = ImplA{}
	a, aok := i.(ImplA)
	if aok {
		fmt.Println(a, "is ImplA")
	}
	b, bok := i.(ImplB)
	if bok {
		fmt.Println(b, "is ImplB")
	} else {
		fmt.Println(b, "is not ImplB")
	}
}

func PrimitiveTypes() {
	var e interface{} = "hello"
	d, ok := e.(int)
	if ok {
		fmt.Println(d, "is an integer")
	}
	f32, ok := e.(float32)
	if ok {
		fmt.Println(f32, "is a float32")
	}
	f64, ok := e.(float32)
	if ok {
		fmt.Println(f64, "is a float64")
	}
	s, ok := e.(string)
	if ok {
		fmt.Println(s, "is a string")
	}
}

func TypeSwitch() {
	var e interface{} = 42
	switch t := e.(type) {
	case int:
		fmt.Println(e, " is an int - ", t)
	case float32:
		fmt.Println(e, " is a float32 - ", t)
	case float64:
		fmt.Println(e, " is a float64 - ", t)
	case string:
		fmt.Println(e, " is a string - ", t)
	default:
		fmt.Println(e, " is of an unknown type - ", t)
	}
}

func main() {
	fmt.Println("inteface/struct types")
	InterfaceTypes()
	PrimitiveTypes()
	TypeSwitch()
}
