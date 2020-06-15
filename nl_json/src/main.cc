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
#include <string>
#include <utility>
#include <variant>

#include "nlohmann/json.hpp"

void CreateSimpleJson() {
  nlohmann::json json;
  json["integer"] = 17;
  json["float"] = 17.0F;
  json["string"] = "seventeen";
  static constexpr int kJsonDumpIndent{2};
  std::cout << "simple json\n" << json.dump(kJsonDumpIndent) << "\n\n";
}

void CreateJsonArray() {
  nlohmann::json json;
  json["int_array"][7] = 8;
  for (int i = 0; 3 > i; ++i) {
    json["int_array"][i] = i;
  }
  static constexpr int kJsonDumpIndent{2};
  std::cout << "json array\n" << json.dump(kJsonDumpIndent) << "\n\n";
}

void CreateJsonMap() {
  static constexpr std::array<std::pair<const char*, int>, 3> kMap{
      std::make_pair("integer_0", 0),
      std::make_pair("integer_1", 1),
      std::make_pair("integer_2", 2),
  };
  nlohmann::json json;
  for (const auto& [key, value] : kMap) {
    json["int_map"][key] = value;
  }
  static constexpr int kJsonDumpIndent{2};
  std::cout << "json map\n" << json.dump(kJsonDumpIndent) << "\n\n";
}

void CreateMultiLevelJsonFromJsonPath() {
  static const std::array<std::variant<int, std::string>, 4> kJsonPath{
      std::variant<int, std::string>{"map_key_0"},
      std::variant<int, std::string>{1},
      std::variant<int, std::string>{"map_key_1"},
      std::variant<int, std::string>{2},
  };

  nlohmann::json json{};
  nlohmann::json* json_path_end = &json;
  int path_index = 0;

  for (const auto& path_end : kJsonPath) {
    if (std::holds_alternative<int>(path_end)) {
      (*json_path_end) = nlohmann::json::array();
      json_path_end = &((*json_path_end)[std::get<int>(path_end)]);
    } else {
      (*json_path_end) = nlohmann::json::object();
      json_path_end = &((*json_path_end)[std::get<std::string>(path_end)]);
    }
    ++path_index;
  }
  (*json_path_end) = "value";
  static constexpr int kJsonDumpIndent{2};
  std::cout << "json from path\n" << json.dump(kJsonDumpIndent) << "\n\n";
}

int main() {
  std::cout << "Hello Niels Lohmann JSON\n";
  std::cout << "Sample code on how to use Niels Lohmann JSON library.\n\n";
  CreateSimpleJson();
  CreateJsonArray();
  CreateJsonMap();
  CreateMultiLevelJsonFromJsonPath();
}
