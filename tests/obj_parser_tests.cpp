//
// Created by Nicholas Solomon on 2026-05-27.
//

#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <parsers/Parsers.h>
#include <shapes/groups/Group.h>
#include <shapes/triangles/Triangle.h>
#include <shapes/Shape.h>

using namespace rtc::parsers;
using namespace rtc::shapes::groups;
using namespace rtc::shapes::triangles;
using namespace rtc::shapes;

SCENARIO("Ignoring unrecognized lines") {
    GIVEN("gibberish <- a file containing:"
          "There was a young lady named Bright"
          "who traveled much faster than light."
          "She set out one day"
          "in a relative way,"
          "and came back the previous night.") {
        std::ifstream gibberish("../input/test/gibberish.obj");
        REQUIRE(gibberish);
        WHEN("parser <- parse_obj_file(gibberish)") {
            const auto parser = parse_obj_file(gibberish);
            THEN("parser.linesIgnored = 5") {
                REQUIRE(parser->lines_ignored == 5);
            }
        }
    }
}

SCENARIO("Vertex records") {
    GIVEN("inputA <- a file containing:"
          "v -1 1 0"
          "v -1.0000 0.5000 0.0000"
          "v 1 0 0"
          "v 1 1 0") {
        std::ifstream inputA("../input/test/inputA.obj");
        REQUIRE(inputA);
        WHEN("parser <- parse_obj_file(inputA)") {
            const auto parser = parse_obj_file(inputA);
            THEN("parser.vertices[1] = point(-1, 1, 0)") {
                REQUIRE(parser->vertices[1] == point(-1, 1, 0));
            }
            AND_THEN("parser.vertices[2] = point(-1, 0.5, 0)") {
                REQUIRE(parser->vertices[2] == point(-1, 0.5, 0));
            }
            AND_THEN("parser.vertices[3] = point(1, 0, 0)") {
                REQUIRE(parser->vertices[3] == point(1, 0, 0));
            }
            AND_THEN("parser.vertices[4] = point(1, 1, 0)") {
                REQUIRE(parser->vertices[4] == point(1, 1, 0));
            }
        }
    }
}

SCENARIO("Parsing triangle faces") {
    GIVEN("inputB <- a file containing:"
          "v -1 1 0"
          "v -1 0 0"
          "v 1 0 0"
          "v 1 1 0"
          ""
          "f 1 2 3"
          "f 1 3 4") {
        std::ifstream inputB("../input/test/inputB.obj");
        REQUIRE(inputB);
        WHEN("parser <- parse_obj_file(inputB), g <- parser.default_group, t1 <- g.shapes[0], t2 <- g.shapes[1]") {
            const auto parser = parse_obj_file(inputB);
            const Group* g = parser->default_group.get();
            const auto* t1 = dynamic_cast<const Triangle*>(&(*g)[0]);
            const auto* t2 = dynamic_cast<const Triangle*>(&(*g)[1]);
            REQUIRE(t1 != nullptr);
            REQUIRE(t2 != nullptr);
            THEN("t1.p1 = parser.vertices[1]") {
                REQUIRE(t1->p1 == parser->vertices[1]);
            }
            AND_THEN("t1.p2 = parser.vertices[2]") {
                REQUIRE(t1->p2 == parser->vertices[2]);
            }
            AND_THEN("t1.p3 = parser.vertices[3]") {
                REQUIRE(t1->p3 == parser->vertices[3]);
            }
            AND_THEN("t2.p1 = parser.vertices[1]") {
                REQUIRE(t2->p1 == parser->vertices[1]);
            }
            AND_THEN("t2.p2 = parser.vertices[3]") {
                REQUIRE(t2->p2 == parser->vertices[3]);
            }
            AND_THEN("t2.p3 = parser.vertices[4]") {
                REQUIRE(t2->p3 == parser->vertices[4]);
            }
        }
    }
}

SCENARIO("Triangulating polygons") {
    GIVEN("inputC <- a file containing:"
          "v -1 1 0"
          "v -1 0 0"
          "v 1 0 0"
          "v 1 1 0"
          "v 0 2 0"
          ""
          "f 1 2 3 4 5") {
        std::ifstream inputC("../input/test/inputC.obj");
        REQUIRE(inputC);
        WHEN("parser <- parse_obj_file(inputC), g <- parser.default_group, t1 <- g.shapes[0], t2 <- g.shapes[1], t3 <- g.shapes[2]") {
            const auto parser = parse_obj_file(inputC);
            const Group* g = parser->default_group.get();
            const auto* t1 = dynamic_cast<const Triangle*>(&(*g)[0]);
            const auto* t2 = dynamic_cast<const Triangle*>(&(*g)[1]);
            const auto* t3 = dynamic_cast<const Triangle*>(&(*g)[2]);
            THEN("t1.p1 = parser.vertices[1]") {
                REQUIRE(t1->p1 == parser->vertices[1]);
            }
            AND_THEN("t1.p2 = parser.vertices[2]") {
                REQUIRE(t1->p2 == parser->vertices[2]);
            }
            AND_THEN("t1.p3 = parser.vertices[3]") {
                REQUIRE(t1->p3 == parser->vertices[3]);
            }
            AND_THEN("t2.p1 = parser.vertices[1]") {
                REQUIRE(t2->p1 == parser->vertices[1]);
            }
            AND_THEN("t2.p2 = parser.vertices[3]") {
                REQUIRE(t2->p2 == parser->vertices[3]);
            }
            AND_THEN("t2.p3 = parser.vertices[4]") {
                REQUIRE(t2->p3 == parser->vertices[4]);
            }
            AND_THEN("t3.p1 = parser.vertices[1]") {
                REQUIRE(t3->p1 == parser->vertices[1]);
            }
            AND_THEN("t3.p2 = parser.vertices[4]") {
                REQUIRE(t3->p2 == parser->vertices[4]);
            }
            AND_THEN("t3.p3 = parser.vertices[5]") {
                REQUIRE(t3->p3 == parser->vertices[5]);
            }
        }
    }
}

SCENARIO("Triangles in groups") {
    GIVEN("file <- the file triangles.obj") {
        std::ifstream file("../input/test/triangles.obj");
        REQUIRE(file);
        WHEN("parser <- parse_obj_file(file), g1 <- FirstGroup from parser, g2 <- SecondGroup from parser,"
             "t1 <- g1[0], t2 <- g2[0]") {
            auto parser = parse_obj_file(file);
            auto g1 = parser->groups.at("FirstGroup").get();
            auto g2 = parser->groups.at("SecondGroup").get();
            const auto* t1 = dynamic_cast<const Triangle*>(&(*g1)[0]);
            const auto* t2 = dynamic_cast<const Triangle*>(&(*g2)[0]);
            THEN("t1.p1 = parser.vertices[1]") {
                REQUIRE(t1->p1 == parser->vertices[1]);
            }
            AND_THEN("t1.p2 = parser.vertices[2]") {
                REQUIRE(t1->p2 == parser->vertices[2]);
            }
            AND_THEN("t1.p3 = parser.vertices[3]") {
                REQUIRE(t1->p3 == parser->vertices[3]);
            }
            AND_THEN("t2.p1 = parser.vertices[1]") {
                REQUIRE(t2->p1 == parser->vertices[1]);
            }
            AND_THEN("t2.p2 = parser.vertices[3]") {
                REQUIRE(t2->p2 == parser->vertices[3]);
            }
            AND_THEN("t2.p3 = parser.vertices[4]") {
                REQUIRE(t2->p3 == parser->vertices[4]);
            }
        }
    }
}

SCENARIO("Converting an OBJ file to a group") {
    GIVEN("file <- the file triangles.obj, parser <- parse_obj_file(file)") {
        std::ifstream file("../input/test/triangles.obj");
        REQUIRE(file);
        auto parser = parse_obj_file(file);
        WHEN("g <- obj_to_group(parser)") {
            const auto g = obj_to_group(std::move(parser));
            THEN("g.size() == 3") {
                REQUIRE(g->size() == 3);
            }
        }
    }
}