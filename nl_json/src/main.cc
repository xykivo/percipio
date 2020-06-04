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

#include <array>
#include <iostream>
#include <utility>

#include "nlohmann/json.hpp"

void CreateSimpleJson() {
  nlohmann::json json;
  json["integer"] = 17;
  json["float"] = 17.0F;
  json["string"] = "seventeen";
  std::cout << "simple json\n" << json << "\n\n";
}

void CreateJsonArray() {
  nlohmann::json json;
  for (int i = 0; 3 > i; ++i) {
    json["int_array"][i] = i;
  }
  std::cout << "json array\n" << json << "\n\n";
}

void CreateJsonMap() {
  nlohmann::json json;
  static constexpr std::array<std::pair<const char*, int>, 3> kMap{
      std::make_pair("integer_0", 0),
      std::make_pair("integer_1", 1),
      std::make_pair("integer_2", 2),
  };
  for (const auto& [key, value] : kMap) {
    json["int_map"][key] = value;
  }
  std::cout << "json map\n" << json << "\n\n";
}

int main() {
  std::cout << "Hello Niels Lohmann JSON\n";
  std::cout << "Sample code on how to use Niels Lohmann JSON library.\n\n";
  CreateSimpleJson();
  CreateJsonArray();
  CreateJsonMap();
}
