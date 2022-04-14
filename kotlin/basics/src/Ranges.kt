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
 * Wrapper class for various range samples
 */
class Ranges {
    companion object {
        /**
        * Simple sample showing Kotlin iteration over a range
        */
        fun iterate(max: Int, s: Int = 1): String {
            var str: String = "Iterating over range [0..$max) step $s"
            for (i in 0..max step s) {
                str = str + " $i"
            }
            return str
        }

        /**
        * Simple sample showing Kotlin reverse iteration over a range
        */
        fun reverseIterate(max: Int): String {
            var str: String = "Iterating over range [$max..0]"
            for (i in max downTo 0) {
                str = str + " $i"
            }
            return str
        }

        /**
        * Simple sample showing Kotlin for each iteration over a range
        */
        fun forEachIterate(max: Int): String {
            var str: String = "Iterating using forEach over range [0..$max]"
            (0..max).forEach {
                str = str + " $it"
            }
            return str
        }

        /**
         * Simple sample checking if a number is in range
         */
        fun isInRange(i: Int, min: Int, max:Int): String {
            if (i in min..max) {
                return "$i in range [$min..$max]"
            }
            return "$i not in range [$min..$max]"
        }


        /**
         * Simple sample checking if a number is not in range
         */
        fun isNotInRange(i: Int, min: Int, max:Int): String {
            if (i !in min..max) {
                return "$i in range [$min..$max]"
            }
            return "$i not in range [$min..$max]"
        }
    }
}