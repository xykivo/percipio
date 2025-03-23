// Copyright (C) 2025 Dror Smolarsky
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

#include <concepts>
#include <iostream>

namespace {

// Simple concept requirement on a type
template <typename T>
  requires std::is_integral_v<T>
void OutputInteger(T integer) {
  std::cout << "T is an integeral concept, integer=" << integer << "\n\n";
}

// Concept requirment on a callable type
template <typename T>
  requires std::is_invocable_v<T>
void CallAFunction(T invocable) {
  std::cout << "T is an invocable concept ";
  invocable();
  std::cout << "\n\n";
}

template <typename T>
T Add(const T& value_a, const T& value_b) {
  return value_a + value_b;
}

// Can be added concept
template <typename T>
concept IsAddable = requires(T value_a, T value_b) {
  { Add(value_a, value_b) } -> std::same_as<T>;
};

// Combining 2 concepts on the 2 template types
template <typename TAddFunc, typename TOperand>
  requires std::is_invocable_v<TAddFunc, TOperand, TOperand> &&
           IsAddable<TOperand>
void CallAddFunction(TAddFunc invocable, TOperand value_a, TOperand value_b) {
  std::cout << "TAddFunc is an invocable concept ";
  invocable(value_a, value_b);
  std::cout << "\n\n";
}

// Composing a concept from 2 concepts
template <typename TAddFunc, typename TOperand>
concept AddCallable =
    std::is_invocable_v<TAddFunc, TOperand, TOperand> && IsAddable<TOperand>;

// Using a composed concept defined above
template <typename TAddFunc, typename TOperand>
  requires AddCallable<TAddFunc, TOperand>
void CallAdd(TAddFunc add, TOperand value_a, TOperand value_b) {
  std::cout << "TAddFunc and TOperand are add callable ";
  add(value_a, value_b);
  std::cout << "\n\n";
}

}  // namespace

int main() {
  std::cout << "C++ concepts sample\n\n";
  static constexpr int kInteger{3};

  OutputInteger(kInteger);

  CallAFunction([]() { std::cout << "foo"; });

  static constexpr int kValueA{1};
  static constexpr int kValueB{2};
  CallAddFunction(
      [](int value_a, int value_b) {
        std::cout << value_a << '+' << value_b << '=' << value_a + value_b;
      },
      kValueA, kValueB);

  CallAdd(
      [](int value_a, int value_b) {
        std::cout << value_a << '+' << value_b << '=' << value_a + value_b;
      },
      kValueA, kValueB);
  return 0;
}
