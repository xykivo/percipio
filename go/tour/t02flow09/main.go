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

// Tour: https://go.dev/tour/flowcontrol/9

package main

import (
	"fmt"
	"runtime"
	"time"
)

func simpleSwitch(i int) {
	switch i {
	case 0:
		fmt.Println("nothing")
	case 1:
		fmt.Println("one")
	case 2:
		fmt.Println("two")
	default:
		fmt.Println("many")
	}
}

func stringSwitch() {
	switch os := runtime.GOOS; os {
	case "darwin":
		fmt.Println("OSX")
	case "freebsd":
		fmt.Println("FreeBSD")
	case "linux":
		fmt.Println("Linux")
	case "windows":
		fmt.Println("Windows")
	default:
		fmt.Println(os)
	}
}

func sqr(i int) int {
	fmt.Println("sqr", i)
	return (i * i)
}

func switchEvaluationOrder(i int) {
	switch i {
	case 0:
		fmt.Println("zero")
	case sqr(i - 2): // only evaluated if 0 != i
		fmt.Println("four", i)
	default:
		fmt.Println("???", i)
	}
}

func switchTrue() {
	t := time.Now()
	switch { // same as switch true - can be used as easy to read if else chain
	case t.Hour() < 6:
		fmt.Println("good dawn")
	case t.Hour() < 12:
		fmt.Println("good morning")
	case t.Hour() < 18:
		fmt.Println("good afternoon")
	default:
		fmt.Println("good night")
	}
}

func main() {
	fmt.Println("switch")
	simpleSwitch(1)
	simpleSwitch(3)
	stringSwitch()
	switchEvaluationOrder(0)
	switchEvaluationOrder(4)
	switchEvaluationOrder(8)
	switchTrue()
}
