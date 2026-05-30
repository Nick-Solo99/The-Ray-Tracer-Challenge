//
// Created by Nicholas Solomon on 2026-05-27.
//

#ifndef RTC_PARSERS_H
#define RTC_PARSERS_H

#include <vector>
#include <unordered_set>
#include <tuples/Tuple.h>
#include <shapes/groups/Group.h>
#include <unordered_map>

using namespace rtc::tuples;

namespace rtc::parsers {
    struct ParsedObj {
        std::vector<Point> vertices = {point(0, 0, 0)};
        std::vector<Vector> normals = {vector(0, 0, 0)};
        int lines_ignored = 0;
        std::unique_ptr<groups::Group> default_group = std::make_unique<groups::Group>();
        std::unordered_map<std::string, std::unique_ptr<groups::Group>> groups{};
    };
    static const inline std::unordered_set<std::string> symbols = {"v", "vn", "f", "g"};

    std::unique_ptr<ParsedObj> parse_obj_file(std::ifstream& file);
    std::unique_ptr<groups::Group> obj_to_group(const std::unique_ptr<ParsedObj> &obj);
}


#endif //RTC_PARSERS_H