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
 * Wrapper class for various collections samples
 */
class Collections {
    companion object {

        /**
         * Iterate over all items in a collection
         */
        fun <T> iterate(collection: Collection<T>): String {
            var str: String = "Iterating over collection"
            for (item in collection) {
                str = str + " $item"
            }
            return str
        }

        /**
         * Check if a given value is in a collection
         */
        fun <T> isValueInCollection(value: T, collection: Collection<T>): String {
            when {
                value in collection -> return "$value in $collection"
                // It's possible to add more * in collection statements here
            }
            return "$value not in $collection"
        }

        /**
         * Filter and sort a given collection
         *
         * This is a sample showing how to execute various collection
         * operations.
         * Other types of collection operations can be found at:
         * https://kotlinlang.org/api/latest/jvm/stdlib/kotlin.collections/
         */
        fun <T> filterAndSort(predicate: (T) -> Boolean, collection: Collection<T>): String {
            val list = collection.filter(predicate).sortedBy{it.hashCode()}
            return "Filtered and sorted $collection to $list"
        }
    }
}