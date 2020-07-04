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
  nlohmann::json* json_path_component = &json;
  int path_index = 0;

  for (const auto& path_component : kJsonPath) {
    if (std::holds_alternative<int>(path_component)) {
      (*json_path_component) = nlohmann::json::array();
      json_path_component =
          &((*json_path_component)[std::get<int>(path_component)]);
    } else {
      (*json_path_component) = nlohmann::json::object();
      json_path_component =
          &((*json_path_component)[std::get<std::string>(path_component)]);
    }
    ++path_index;
  }
  (*json_path_component) = "value";
  static constexpr int kJsonDumpIndent{2};
  std::cout << "json from path\n" << json.dump(kJsonDumpIndent) << "\n";

  std::cout << "Access json path - ";
  json_path_component = &json;
  for (const auto& path_component : kJsonPath) {
    switch (json_path_component->type()) {
      case nlohmann::json::value_t::object:
        if (!std::holds_alternative<std::string>(path_component)) {
          std::cerr << "invalid map key " << std::get<int>(path_component)
                    << '\n';
          return;
        } else if (!json_path_component->contains(
                       std::get<std::string>(path_component))) {
          std::cerr << "map key not found "
                    << std::get<std::string>(path_component) << '\n';
          return;
        }
        json_path_component =
            &((*json_path_component)[std::get<std::string>(path_component)]);
        break;
      case nlohmann::json::value_t::array:
        if (!std::holds_alternative<int>(path_component)) {
          std::cerr << "invalid array index "
                    << std::get<std::string>(path_component) << '\n';
          return;
        } else if (std::get<int>(path_component) >=
                   json_path_component->size()) {
          std::cerr << "array index out of bounds "
                    << std::get<int>(path_component) << '\n';
          return;
        }
        json_path_component =
            &((*json_path_component)[std::get<int>(path_component)]);
        break;
      default:
        std::cerr << "Invalid json path component\n";
        return;
    }
  }
  // Becaues of the way the path is set, it is known the value is a string
  std::cout << "json path value = " << json_path_component->get<std::string>()
            << "\n\n";
}

void CopyJson() {
  nlohmann::json src_json{};
  src_json["array"][0] = 0;
  src_json["array"][1] = 1;
  src_json["array"][2] = 2;
  src_json["array"][3] = 3;
  src_json["map"]["key-0"] = "value-0";
  src_json["map"]["key-1"] = "value-1";
  src_json["map"]["key-2"] = "value-2";
  src_json["map"]["key-3"] = "value-3";

  static constexpr int kJsonDumpIndent{2};
  std::cout << "copy json src\n" << src_json.dump(kJsonDumpIndent) << "\n";
  nlohmann::json dst_json_ctr{src_json};
  dst_json_ctr["array"][1] = -1;
  std::cout << "copy json dst(ctr)\n"
            << dst_json_ctr.dump(kJsonDumpIndent) << "\n";
  nlohmann::json dst_json_op = src_json;
  dst_json_op["array"][2] = -2;
  std::cout << "copy json dst(op)\n"
            << dst_json_op.dump(kJsonDumpIndent) << "\n";
}

int main() {
  std::cout << "Hello Niels Lohmann JSON\n";
  std::cout << "Sample code on how to use Niels Lohmann JSON library.\n\n";
  CreateSimpleJson();
  CreateJsonArray();
  CreateJsonMap();
  CreateMultiLevelJsonFromJsonPath();
  CopyJson();
}
