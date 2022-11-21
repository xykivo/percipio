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

/**
 * Wrapper class for various object (and object oriented) related idioms samples.
 */
class Object(val number: Int) {
    var name: String = "noname"

    fun foo() = "foo"

    fun bar() : String = "bar"

    fun numberToString() = when (number) {
        0 -> "zero"
        1 -> "one"
        else -> "many"
    }

    companion object {
        /**
         * Example of using a with expression to call multiple methods of an
         * object
         */
        fun multipleObjectCalls(obj: Object) {
            with (obj) {
                println("  ${obj.name}")
                println("  ${obj.foo()}")
                println("  ${obj.bar()}")
                println("  ${obj.numberToString()}")
            }
        }

        /**
         * Example of configuring the properties of an object
         *
         * This is useful in cases where object fields that are not present in
         * the object constructor.
         */
        fun configureObjectProperties() {
            val obj = Object(11).apply {
                name = "eleven"
            }
            println("  ${obj.name} - ${obj.number}");
        }

    }
}