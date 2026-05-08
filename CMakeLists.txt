cmake_minimum_required(VERSION 4.0)
project(RTC)

set(CMAKE_CXX_STANDARD 23)

find_package(Catch2 3 REQUIRED)

add_library(rtc_core
    src/tuples/Tuple.cpp
        src/canvas/Canvas.cpp
        src/canvas/Canvas.h
        src/matrices/Matrix.cpp
        src/matrices/Matrix.h
)

target_include_directories(rtc_core PUBLIC src)

add_executable(tests
        tests/test.cpp
        tests/tuples_tests.cpp
        tests/canvas_tests.cpp
        tests/matrices_tests.cpp
)
target_link_libraries(tests
        PRIVATE rtc_core
        PRIVATE Catch2::Catch2WithMain
)

add_executable(Exercises
        exercises/Cannon.cpp

)

target_link_libraries(Exercises
        PRIVATE rtc_core
)

add_executable(RTC main.cpp)

target_link_libraries(RTC
    PRIVATE rtc_core
)
