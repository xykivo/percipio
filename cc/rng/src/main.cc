// BSD 3-Clause License
//
// Copyright (c) 2020-2021, Dror Smolarsky
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
#include <random>

namespace {

/// Generate N series of random integers using a uniform random distribution
/// with the default random device.
void UniformIntDistributionWithDefaultSeed(int series_count, int series_size) {
  std::random_device rng_device;
  std::mt19937_64 rng_generator(rng_device());
  static constexpr int kMinInt = 1;
  static constexpr int kMaxInt = 11;
  std::uniform_int_distribution<> rng_distribution(kMinInt, kMaxInt);
  std::cout << "uniform int distribution  - default seed\n";
  for (int si = 0; si < series_count; ++si) {
    std::cout << "\tseries " << si << "\n\t\t";
    for (int i = 0; i < series_size; ++i) {
      std::cout << " " << rng_distribution(rng_generator);
    }
    std::cout << '\n';
  }
}

/// Generate N series of random integers using a uniform random distribution
/// using the same constant seed for every series.
void UniformIntDistributionWithConstantSeed(int series_count, int series_size) {
  static constexpr int64_t kSeed = 1;
  std::mt19937_64 rng_generator(kSeed);
  static constexpr int kMinInt = 1;
  static constexpr int kMaxInt = 11;
  std::uniform_int_distribution<> rng_distribution(kMinInt, kMaxInt);
  std::cout << "uniform int distribution  - constant seed\n";
  for (int si = 0; si < series_count; ++si) {
    std::cout << "\tseries " << si << "\n\t\t";
    for (int i = 0; i < series_size; ++i) {
      std::cout << " " << rng_distribution(rng_generator);
    }
    std::cout << '\n';
  }
}

}  // namespace

/// C++ random main entry point
int main() {
  std::cout << "STL random samples\n";
  static constexpr int kSeriesCount = 2;
  static constexpr int kSeriesSize = 21;
  UniformIntDistributionWithDefaultSeed(kSeriesCount, kSeriesSize);
  UniformIntDistributionWithConstantSeed(kSeriesCount, kSeriesSize);
  UniformIntDistributionWithConstantSeed(kSeriesCount, kSeriesSize);
  return 0;
}
