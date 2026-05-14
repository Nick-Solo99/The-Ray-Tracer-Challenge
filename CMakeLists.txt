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
        src/transformations/Transformations.cpp
        src/transformations/Transformations.h
        src/rays/Ray.cpp
        src/rays/Ray.h
        src/shapes/spheres/Sphere.cpp
        src/shapes/spheres/Sphere.h
        src/intersections/Intersection.cpp
        src/intersections/Intersection.h
        src/shapes/Shape.cpp
        src/shapes/Shape.h
        src/lights/Light.cpp
        src/lights/Light.h
        src/lights/point/PointLight.cpp
        src/lights/point/PointLight.h
        src/materials/Material.cpp
        src/materials/Material.h
        src/world/World.cpp
        src/world/World.h
        src/camera/Camera.cpp
        src/camera/Camera.h
)

target_include_directories(rtc_core PUBLIC src)

add_executable(tests
        tests/test.cpp
        tests/tuples_tests.cpp
        tests/canvas_tests.cpp
        tests/matrices_tests.cpp
        tests/transformations_tests.cpp
        tests/rays_tests.cpp
        tests/spheres_tests.cpp
        tests/intersections_tests.cpp
        tests/lights_tests.cpp
        tests/materials_tests.cpp
        tests/world_tests.cpp
        tests/camera_tests.cpp
)
target_link_libraries(tests
        PRIVATE rtc_core
        PRIVATE Catch2::Catch2WithMain
)

add_executable(Cannon
        exercises/Cannon.cpp

)

target_link_libraries(Cannon
        PRIVATE rtc_core
)

add_executable(MatrixExperiments
        exercises/MatrixExperiments.cpp
)

target_link_libraries(MatrixExperiments
        PRIVATE rtc_core
)

add_executable(RTC main.cpp)

target_link_libraries(RTC
    PRIVATE rtc_core
)
add_executable(ClockPixels exercises/ClockPixels.cpp)
target_link_libraries(ClockPixels PRIVATE rtc_core)
add_executable(FirstShadow exercises/FirstShadow.cpp)
target_link_libraries(FirstShadow PRIVATE rtc_core)

add_executable(FirstShading exercises/FirstShading.cpp)
target_link_libraries(FirstShading PRIVATE rtc_core)
add_executable(FirstScene exercises/FirstScene.cpp
        exercises/FirstScene.cpp)
target_link_libraries(FirstScene PRIVATE rtc_core)
