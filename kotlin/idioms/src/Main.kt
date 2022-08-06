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

package com.xykivo.percipio.idioms

fun printDataClassesSamples() {
    println("Data classes")
    val someData = DataClasses.SomeData(0, "Zero")
    println("  SomeData=${someData.toString()}")
    println()
}

fun printDefaultFunctionValuesSamples() {
    println("Default function arguments")
    println(" int to string (default): ${DefaultFunctionValues.IntToString()}")
    println(" int to string: ${DefaultFunctionValues.IntToString(1)}")
    println()
}

fun printFilterCollectionSamples() {
    println("Filter collection")
    val fibonachiList = listOf<Int>(0, 1, 2, 3, 5, 8, 13, 21, 34)
    val isEven: (Int) -> Boolean = {i: Int -> 0 == (i % 2)}
    println("Filter ${fibonachiList} for even number: ${Collections.filterCollection(fibonachiList, isEven)}")
}

fun printInstanceChecksSamples() {
    println("Instance checks")
    val i = 2
    println("$i is a ${InstanceChecks.objectTypeToString(i)}")
    val f = 3.0F
    println("$f is a ${InstanceChecks.objectTypeToString(f)}")
    val s = "string"
    println("$s is a ${InstanceChecks.objectTypeToString(s)}")
    println()
}

fun printAccessMap() {
    println("Map access")
    val numberMap = mapOf("zero" to 0, "one" to 1, "two" to 2, "three" to 3)
    println("Access numberMap[zero]=${numberMap["three"]}")
    println("Access numberMap[two]=${numberMap["two"]}")
    println()
}

fun printTraverseMap() {
    println("Traverse map")
    val numberMap = mapOf("zero" to 0, "one" to 1, "two" to 2, "three" to 3)
    for ((k, v) in numberMap) {
        println("  $k $v")
    }
    println()
}

fun printPropertiesSamples() {
    println("Properties")
    val p = Properties()
    println(p.property)
    println(p.lazyProperty)
    println()
}

fun printExtensionFunctionSamples() {
    println("Extension functions")
    var str = "some string"
    print("$str -> ${str.spacesToUnderscores()}")
    println()
}

fun printSingletonSamples() {
    println("Singletons")
    println("count=${Singleton.count}")
    println("count=${Singleton.count}")
    println("count=${Singleton.count}")
    println()
}

fun printAbstractClassSamples() {
    println("Abstract class")
    AbstractClass.instantiateAbstractClass()
    println()
}

fun printIsNullSamples() {
    println("Is null idioms")
    var obj: String? = null
    println("is not null else: ${IsNull.isNotNullElse(obj)}")
    println("is not null else code block: ${IsNull.isNotNullElseCodeBlock(obj)}")
    println("execute if null: ${IsNull.executeIfNull(obj)}")
    println("execute if not null: ${IsNull.executeIfNotNull(obj)}")
    obj = "string"
    println("is not null else: ${IsNull.isNotNullElse(obj)}")
    println("is not null else code block: ${IsNull.isNotNullElseCodeBlock(obj)}")
    println("execute if null: ${IsNull.executeIfNull(obj)}")
    println("execute if not null: ${IsNull.executeIfNotNull(obj)}")
    var arrayList = ArrayList<Int>()
    println("first item in possible empty collection: ${IsNull.firstItemInPossiblyEmptyCollection(arrayList)}")
    arrayList.add(0)
    println("first item in possible empty collection: ${IsNull.firstItemInPossiblyEmptyCollection(arrayList)}")
    println()
    var v : Int? = null
    val square = { i: Int -> i * i }
    var t = IsNull.mapNullableValue(v, -1, square)
    println("transform value if not null: $v -> $t")
    v = 2
    t = IsNull.mapNullableValue(v, -1, square)
    println("transform value if not null: $v -> $t")
    println()
}

fun main() {
    println("hello kotlin idioms")
    println()
    printDataClassesSamples()
    printDefaultFunctionValuesSamples()
    printFilterCollectionSamples()
    printInstanceChecksSamples()
    printAccessMap()
    printTraverseMap()
    printPropertiesSamples()
    printExtensionFunctionSamples()
    printSingletonSamples()
    printAbstractClassSamples()
    printIsNullSamples()
}
