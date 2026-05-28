//
// Created by Nicholas Solomon on 2026-05-27.
//

#include "Parsers.h"
#include <string>
#include <fstream>
#include <ranges>
#include <sstream>
#include <shapes/triangles/Triangle.h>

using namespace rtc::shapes::triangles;

namespace rtc::parsers {
    std::unique_ptr<ParsedObj> parse_obj_file(std::ifstream &file) {
        auto result = std::make_unique<ParsedObj>();
        std::string line;
        groups::Group* cur_group = result->default_group.get();
        while (std::getline(file, line)) {
            std::stringstream ss(line);

            std::string symbol;
            if (!(ss >> symbol)) {
                continue;
            }

            if (!symbols.contains(symbol)) {
                ++result->lines_ignored;
                continue;
            }

            if (symbol == "v") {
                float x, y, z;
                ss >> x >> y >> z;
                result->vertices.push_back(point(x, y, z));
            } else if (symbol == "f") {
                std::vector<int> indices;
                std::string token;
                while (ss >> token) {
                    indices.push_back(std::stoi(token));
                }
                for (int i = 1; i + 1 < indices.size(); ++i) {
                    cur_group->add_child(std::make_unique<Triangle>(result->vertices[indices[0]], result->vertices[indices[i]], result->vertices[indices[i + 1]]));
                }
            } else if (symbol == "g") {
                std::string group_name;
                ss >> group_name;

                auto& ptr = result->groups[group_name];

                if (!ptr) {
                    ptr = std::make_unique<groups::Group>();
                }

                cur_group = ptr.get();
            }
        }
        return result;
    }

    std::unique_ptr<groups::Group> obj_to_group(const std::unique_ptr<ParsedObj> &obj) {
        auto result = std::make_unique<groups::Group>();
        result->add_child(std::move(obj->default_group));
        for (auto &group: obj->groups | std::views::values) {
            result->add_child(std::move(group));
        }
        return result;
    }
}
