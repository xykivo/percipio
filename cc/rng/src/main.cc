// Copyright (C) 2020 Dror Smolarsky
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

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
