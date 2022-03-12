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

/**
 * Wrapper class for various control flow samples functions
 */
class ControlFlow {
    companion object {
        /**
         * Simple sample showing Kotlin conditional (if/else) expression
         */
        fun conditionalExpression(b: Boolean): String {
            if (b) {
               return "b is true"
            }
            else {
              return "b is false"
            }
        }

        /**
         * Simple sample showing Kotlin for loop in all collection elements
         */
        fun forLoop(stringList: List<String>): String {
            var str: String =  "for loop (over list):"
            for (s in stringList) {
                str = str + " $s"
            }
            return str
        }

        /**
         * Simple sample showing Kotlin for and indexed based for loop
         */
        fun indexedForLoop(stringList: List<String>): String {
            var str: String =  "indexed for loop (over list):"
            for (i in stringList.indices) {
                str = str + " $i.${stringList[i]}"
            }
            return str
        }

        /**
         * Simple sample showing Kotlin while loop
         */
        fun whileLoop(max: Int): String {
            var str: String = "while loop from 0 to $max:"
            var i: Int = 0
            while (i < max) {
                str = str + " $i"
                ++i
            }
            return str
        }

        /**
         * Simple sample showing Kotlin values based which expression
         */
        fun whenValue(value: Int): String {
            when (value) {
                1 -> return "$value is one"
                2 -> return "$value is two"
                3 -> return "$value is three"
                else -> return "$value is bigger than three"
            }
            return "opps, should not be here"
        }

        /**
         * Simple sample showing Kotlin type based which expression
         *
         * Note that which expression can support combined type and value
         * cases.
         */
        fun whenType(value: Any): String {
            when (value) {
                is Int -> return "$value is Int"
                is String -> return "$value is String"
            }
            return "$value type unknown"
        }
    }
}
