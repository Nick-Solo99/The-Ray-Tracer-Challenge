//
// Created by Nicholas Solomon on 2026-05-07.
//

#include <catch2/catch_test_macros.hpp>
#include "canvas/Canvas.h"

using namespace rtc::canvas;

SCENARIO("Creating a canvas") {
    GIVEN("c <- canvas(10, 20)") {
        const Canvas c(10, 20);

        THEN("c.width = 10") {
            REQUIRE(c.width == 10);
        }

        AND_THEN("c.height = 20") {
            REQUIRE(c.height == 20);
        }

        AND_THEN("every pixel of c is color(0.0, 0.0, 0.0)") {
            bool isBlack = true;
            for (Color pixel : c.pixels) {
                if (pixel != color(0, 0, 0)) {
                    isBlack = false;
                }
            }
            REQUIRE(isBlack);
        }
    }
}

SCENARIO("Writing pixels to a canvas") {
    GIVEN("c <- canvas(10, 20), red <- color(1, 0, 0)") {
        Canvas c(10, 20);
        const Color red = color(1, 0, 0);

        WHEN("c.write_pixel(2, 3, red)") {
            c.write_pixel(2, 3, red);

            THEN("pixel_at(c, 2, 3) = red") {
                REQUIRE(c.pixel_at(2, 3) == red);
            }
        }
    }
}

SCENARIO("Constructing the PPM Header") {
    GIVEN("c <- canvas(5, 3)") {
        Canvas c(5, 3);
        WHEN("ppm <- c.canvas_to_ppm()") {
            std::string ppm = c.canvas_to_ppm();
            THEN("lines 1 - 3 of ppm are correct") {
                std::stringstream ss(ppm);
                std::string line;

                REQUIRE(std::getline(ss, line));
                REQUIRE(line == "P3");

                REQUIRE(std::getline(ss, line));
                REQUIRE(line == "5 3");

                REQUIRE(std::getline(ss, line));
                REQUIRE(line == "255");
            }
        }
    }
}

SCENARIO("Constructing the PPM pixel data") {
    GIVEN("c <- canvas(5, 3), c1 <- color(1.5, 0, 0), c2 <- color(0, 0.5, 0), c3 <- color(-0.5, 0, 1") {
        Canvas c(5, 3);
        Color c1 = color(1.5, 0, 0);
        Color c2 = color(0, 0.5, 0);
        Color c3 = color(-0.5, 0, 1);

        WHEN("c.write_pixel(0, 0, c1), c.write_pixel(2, 1, c2), c.write_pixel(4, 2, c3), ppm <- c.canvas_to_ppm()") {
            c.write_pixel(0, 0, c1);
            c.write_pixel(2, 1, c2);
            c.write_pixel(4, 2, c3);
            std::string ppm = c.canvas_to_ppm();

            THEN("lines 4-6 of ppm are correct") {
                std::vector<std::string> lines;
                std::stringstream ss(ppm);
                std::string line;

                while (std::getline(ss, line)) {
                    lines.push_back(line);
                }

                REQUIRE(lines[3] == "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
                REQUIRE(lines[4] == "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0");
                REQUIRE(lines[5] == "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255");
            }
        }
    }
}

SCENARIO("Splitting long lines in PPM files") {
    GIVEN("c <- canvas(10, 2)") {
        Canvas c(10, 2);

        WHEN("every pixel of c is color(1, 0.8, 0.6), ppm <- c.canvas_to_ppm()") {
            for (size_t y = 0; y < c.height; ++y) {
                for (size_t x = 0; x < c.width; ++x) {
                    c.write_pixel(x, y, color(1.0f, 0.8f, 0.6f));
                }
            }
            std::string ppm = c.canvas_to_ppm();

            THEN("lines 4-7 of ppm are correct") {
                std::vector<std::string> lines;
                std::stringstream ss(ppm);
                std::string line;

                while (std::getline(ss, line)) {
                    lines.push_back(line);
                }

                REQUIRE(lines.size() >= 7);

                REQUIRE(lines[3] == "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");
                REQUIRE(lines[4] == "153 255 204 153 255 204 153 255 204 153 255 204 153");
                REQUIRE(lines[5] == "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");
                REQUIRE(lines[6] == "153 255 204 153 255 204 153 255 204 153 255 204 153");
            }
        }
    }
}

SCENARIO("PPM files are terminated by a newline character") {
    GIVEN("c <- canvas(5, 3)") {
        Canvas c(5, 3);
        WHEN("ppm <- c.canvas_to_ppm()") {
            std::string ppm = c.canvas_to_ppm();

            THEN("ppm ends with a newline character") {
                REQUIRE(!ppm.empty());
                REQUIRE(ppm.back() == '\n');
            }
        }
    }
}