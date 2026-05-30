//
// Created by Nicholas Solomon on 2026-05-27.
//

#include "Parsers.h"
#include <string>
#include <fstream>
#include <ranges>
#include <sstream>
#include <shapes/triangles/Triangle.h>
#include <shapes/triangles/SmoothTriangle.h>

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
            } else if (symbol == "vn") {
                float x, y, z;
                ss >> x >> y >> z;
                result->normals.push_back(vector(x, y, z));
            } else if (symbol == "f") {
                std::vector<int> v_indices;
                std::vector<int> n_indices;
                std::string token;
                while (ss >> token) {
                    std::vector<int> values;
                    auto slash_count = std::ranges::count(token, '/');
                    if (slash_count == 0) {
                        v_indices.push_back(std::stoi(token));
                    } else if (slash_count == 1) {
                        for (auto part : std::views::split(token, '/')) {
                            std::string s(part.begin(), part.end());
                            if (s.empty()) continue;
                            values.push_back(std::stoi(s));
                        }
                        v_indices.push_back(values[0]);
                    } else if (slash_count == 2){
                        for (auto part : std::views::split(token, '/')) {
                            std::string s(part.begin(), part.end());
                            if (s.empty()) continue;
                            values.push_back(std::stoi(s));
                        }
                        if (values.size() == 2) {
                            v_indices.push_back(values[0]);
                            n_indices.push_back(values[1]);
                        } else {
                            v_indices.push_back(values[0]);
                            n_indices.push_back(values[2]);
                        }
                    }
                }
                for (int i = 1; i + 1 < v_indices.size(); ++i) {
                    auto slash_count = std::ranges::count(token, '/');
                    if (slash_count == 0 || slash_count == 1) {
                        cur_group->add_child(std::make_unique<Triangle>(
                            result->vertices[v_indices[0]],
                            result->vertices[v_indices[i]],
                            result->vertices[v_indices[i + 1]]
                            ));
                    } else if (slash_count == 2) {
                        cur_group->add_child(std::make_unique<SmoothTriangle>(
                                result->vertices[v_indices[0]],
                                result->vertices[v_indices[i]],
                                result->vertices[v_indices[i + 1]],
                                result->normals[n_indices[0]],
                                result->normals[n_indices[i]],
                                result->normals[n_indices[i + 1]]
                                ));
                    }
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
