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

// Tour: https://go.dev/tour/concurrency/1

package main

import (
	"fmt"
	"sync"
)

var routineWaitGroup sync.WaitGroup

func Routine(name string) {
	defer routineWaitGroup.Done()
	fmt.Println("running routine", name)
}

func SimpleGoRoutine() {
	fmt.Println("simple go routine")
	for _, v := range []string{"a", "b", "c", "d"} {
		routineWaitGroup.Add(1)
		go Routine(v)
	}
	routineWaitGroup.Add(1)
	Routine("z")
	routineWaitGroup.Wait()
}

func Multiply(input chan int, output chan int) {
	a, b := <- input, <- input
	output <- a * b
}

func Channels() {
	fmt.Println("channles")
	inputChannel := make(chan int)
	outputChannel := make(chan int)
	go Multiply(inputChannel, outputChannel)
	inputChannel <- 2
	inputChannel <- 2
	result := <- outputChannel
	fmt.Println(2, "*", 2 , "=", result)
}

func BufferedChannels() {
	fmt.Println("buffered channles")
	const callCount = 3
	const channelSize = 3
	c := make(chan int, channelSize)
	var waitGroup sync.WaitGroup
	waitGroup.Add(callCount)
	go func() {
		for i := 0 ; callCount > i ; i++ {
			defer waitGroup.Done()
			x := <- c
			y := <- c
			z := <- c
			if (x + y) > z {
				fmt.Println(x, "+", y, ">", z)
			} else {
				fmt.Println(x, "+", y, "<", z)
			}
		}
	} ()
	go func() {
		for i := 0 ; (callCount * channelSize) > i ; i++ {
			c <- i
		}
	} ()
	waitGroup.Wait()
}

func ChannelIsClosed() {
	fmt.Println("channel is closed")
	c := make(chan int)
	go func () {
		x, y := 0, 1
		for i := 0 ; 10 > i ; i++ {
			c <- x
			x, y = y, x + y
		}
		close(c)
	} ()
	i, ok := <- c
	for ; true == ok ; {
		fmt.Print(i, " ")
		i, ok = <- c
	}
	fmt.Println()
}

func ChannelRangeAndClose() {
	fmt.Println("channel range and close")
	c := make(chan int)
	go func () {
		x, y := 0, 1
		for i := 0 ; 10 > i ; i++ {
			c <- x
			x, y = y, x + y
		}
		close(c)
	} ()
	for i := range c {
		fmt.Print(i, " ")
	}
	fmt.Println()
}

func SelectChannel() {
	fmt.Println("select channel")
	c := make(chan int)
	q := make(chan int)
	go func() {
		for i := 0 ; 11 > i ; i++ {
			fmt.Print(<- c, " ")
		}
		q <- 0
	} ()
	x, y := 0, 1
	for {
		select {
		case c <- x:
			x, y = y, x + y
		case <- q:
			fmt.Println()
			return
		}
	}
}

func Mutex() {
	fmt.Println("mutex")
	var mutex sync.Mutex
	dna := ""
	var waitGroup sync.WaitGroup
	waitGroup.Add(4)
	nucleus := func(n string, c int) {
		defer waitGroup.Done()
		for i := 0 ; c > i ; i++ {
			mutex.Lock()
			dna += n
			mutex.Unlock()
		}
	}
	go nucleus("c", 4)
	go nucleus("a", 4)
	go nucleus("g", 4)
	go nucleus("t", 4)
	waitGroup.Wait()
	fmt.Println(dna)
}

func main() {
	fmt.Println("go routines")
	SimpleGoRoutine()
	Channels()
	BufferedChannels()
	ChannelIsClosed()
	ChannelRangeAndClose()
	SelectChannel()
	Mutex()
}
