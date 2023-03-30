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

#include <iostream>
#include <mutex>
#include <string_view>
#include <thread>

namespace {

std::mutex mtx{};
int counter{0};

void WorkerFunction(std::string_view name, int count, int skip) {
  std::scoped_lock lock(mtx);
  for (int i = 0; i < count; ++i) {
    counter += skip;
    std::cout << name << " counting - " << i << " counter=" << counter
              << std::endl;
  }
}

}  // namespace

int main() {
  std::cout << "STL std::mutex sample" << std::endl;
  static constexpr int kThread0Count{16};
  static constexpr int kThread0Skip{2};
  std::thread thread_0{WorkerFunction, "thread_0", kThread0Count, kThread0Skip};
  static constexpr int kThread1Count{8};
  static constexpr int kThread1Skip{1};
  std::thread thread_1{WorkerFunction, "thread_1", kThread1Count, kThread1Skip};
  thread_0.join();
  thread_1.join();
}
