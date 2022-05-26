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
 * Wrapper class for various is null idioms samples
 */
class IsNull {
    companion object {
        /**
         * Do if null else check using the ?. operator
         */
        fun <T> isNotNullElse(obj: T?) : String {
            return obj?.toString() ?: "is null"
        }

        /**
         * Do if null else check using the ?. operator in a code block
         */
        fun <T> isNotNullElseCodeBlock(obj: T?) : String {
            val str = obj?.toString() ?: run  {
                return "is null"
            }
            return str
        }

        /**
         * Execute a statement if object is null
         */
        fun <T> executeIfNull(obj: T?) : String {
            obj ?: return "is null"
            return obj.toString()
        }

        /**
         * Execute a statement if object is not null
         */
        fun <T> executeIfNotNull(obj: T?): String {
            obj?.let {
                return obj.toString()
            }
            return "is null"
        }

        /**
         * Check if a collection is empty
         *
         * @return String representation of the first item in the collection,
         *         or a collection if empty string if the collection is empty.
         */
        fun <T> firstItemInPossiblyEmptyCollection(collection: Collection<T>): String {
            val item: T?= collection.firstOrNull()
            if (null == item) {
                return "collection is empty"
            }
            return item.toString()
        }
    }
}