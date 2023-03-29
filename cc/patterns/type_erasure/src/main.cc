// BSD 3-Clause License
//
// Copyright (c) 2021, Dror Smolarsky
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

namespace {

class Func {
 public:
  template <typename F>
  // NOLINTNEXTLINE(google-explicit-constructor)
  Func(F f) : f_(new CallableImpl<F>(f)) {}

  ~Func() { delete f_; }

  template <typename F, typename... Args>
  // NOLINTNEXTLINE(google-explicit-constructor)
  Func(F f, Args... args) : f_(new CallableImpl<F, Args...>(f, args...)) {}

  void operator()() { f_->Execute(); }

 private:
  class Callable {
   public:
    virtual ~Callable() = default;
    virtual void Execute() = 0;
  };

  template <typename F, typename... Args>
  class CallableImpl : public Callable {
   public:
    // NOLINTNEXTLINE(google-explicit-constructor, misc-unused-parameters)
    CallableImpl(F f, Args... args) : f_(f) {}
    ~CallableImpl() override = default;
    void Execute() override { f_(); }

   private:
    F f_;
  };

  Callable* f_;
};

int count = 0;
void CallFunc(Func f) {
  ++count;
  f();
}

}  // namespace

int main(int argc, char* argv[]) {
  (void)argc;
  (void)argv;
  std::cout << "Sample implementation of the type erasure design pattern\n";
  CallFunc([]() {
    std::cout << "Call function with no arguments " << count << std::endl;
  });
  CallFunc([=]() {
    std::cout << "Call function with captured (by value) arguments " << count
              << std::endl;
  });
}
