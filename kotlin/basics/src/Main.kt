// BSD 3-Clause License
//
// Copyright (c) 2022, Dror Smolarsky
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

package com.xykivo.percipio.basics

fun printFunctionSamples() {
    println("Functions:")
    Functions.printStrings(listOf<String>("string-0", "string-1", "string-2"))
    println("3 + 5 = ${Functions.add(3, 5)}")
    println()
}

fun printVariableSamples() {
    println("Global variables")
    println("float=${float}")
    println("integer=${integer}")
    println("FLOAT=${FLOAT}")
    println("INTEGER=${INTEGER}")
    println("variable float=${vfloat}")
    println("variable integer=${vinteger}")
    println()
    println("Class variables")
    println("float=${Variables.float}")
    println("integer=${Variables.integer}")
    println("FLOAT=${Variables.FLOAT}")
    println("INTEGER=${Variables.INTEGER}")
    println("variable float=${Variables.vfloat}")
    println("variable integer=${Variables.vinteger}")
    println()
}

fun printClassesSample() {
    var car = Car(Position(0F, 0F, 0F))
    println("Car created at ${car.position}")
    car.move(1F, 1F, 1F)
    println("Car moved to ${car.position}")
}

fun printControlFlowSamples() {
    println(ControlFlow.conditionalExpression(false));
    println(ControlFlow.conditionalExpression(true));
    val strList = listOf<String>("string-0", "string-1", "string-2")
    println(ControlFlow.forLoop(strList));
    println(ControlFlow.indexedForLoop(strList));
    println(ControlFlow.whileLoop(8))
    println(ControlFlow.whenValue(1))
    println(ControlFlow.whenValue(4))
    println(ControlFlow.whenType(4))
    println(ControlFlow.whenType("yada"))
    println()
}

fun printRangesSamples() {
    println(Ranges.iterate(5))
    println(Ranges.iterate(8, 2))
    println(Ranges.isInRange(0, -5, 5))
    println(Ranges.isInRange(8, -5, 5))
    println(Ranges.isNotInRange(0, -5, 5))
    println(Ranges.isNotInRange(8, -5, 5))
    println()
}

fun printCollectionsSamples() {
    val fibonachiSeries = listOf<Int>(0, 1, 2, 3, 5, 8, 13, 21, 34)
    println(Collections.iterate(fibonachiSeries))
    println(Collections.isValueInCollection(2, fibonachiSeries))
    println(Collections.isValueInCollection(4, fibonachiSeries))
    val unsortedFibonachiSeries = listOf<Int>(8, 13, 0, 1, 2, 21, 34, 3, 5)
    val isEven: (Int) -> Boolean = {i: Int -> 0 == (i % 2)}
    println(Collections.filterAndSort<Int>(isEven, unsortedFibonachiSeries))
    println()
}

fun printNullableSamples() {
    var i: Int? = null
    println(Nullable.IsNull(i))
    i = 8
    println(Nullable.IsNull(i))
    println()
}

fun main() {
    println("hello kotlin basics")
    println()
    printFunctionSamples()
    printVariableSamples()
    printClassesSample()
    printControlFlowSamples()
    printRangesSamples()
    printCollectionsSamples()
    printNullableSamples()
}
