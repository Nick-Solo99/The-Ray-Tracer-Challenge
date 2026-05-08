cmake_minimum_required(VERSION 4.0)
project(RTC)

set(CMAKE_CXX_STANDARD 20)

find_package(Catch2 3 REQUIRED)

add_library(rtc_core
    src/tuples/Tuple.cpp
)

target_include_directories(rtc_core PUBLIC src)

add_executable(tests
        tests/test.cpp
        tests/tuples_tests.cpp
)
target_link_libraries(tests
        PRIVATE rtc_core
        PRIVATE Catch2::Catch2WithMain
)

add_executable(RTC main.cpp)

target_link_libraries(RTC
    PRIVATE rtc_core
)
