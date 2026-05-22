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
        src/shapes/planes/Plane.cpp
        src/shapes/planes/Plane.h
        src/constants/Constants.h
        src/patterns/Pattern.cpp
        src/patterns/Pattern.h
        src/patterns/stripes/StripePattern.cpp
        src/patterns/stripes/StripePattern.h
        src/patterns/gradients/GradientPattern.cpp
        src/patterns/gradients/GradientPattern.h
        src/patterns/rings/RingPattern.cpp
        src/patterns/rings/RingPattern.h
        src/patterns/checkers/CheckerPattern.cpp
        src/patterns/checkers/CheckerPattern.h
        src/patterns/gradients/RadialGradientPattern.cpp
        src/patterns/gradients/RadialGradientPattern.h
        src/patterns/solid/SolidPattern.cpp
        src/patterns/solid/SolidPattern.h
        src/patterns/binary/BinaryPattern.h
        src/patterns/blended/BlendedPattern.cpp
        src/patterns/blended/BlendedPattern.h
        src/noise/PerlinNoise.cpp
        src/noise/PerlinNoise.h
        src/patterns/perturbed/PerturbedPattern.cpp
        src/patterns/perturbed/PerturbedPattern.h
        src/patterns/test/TestPattern.cpp
        src/patterns/test/TestPattern.h
        src/shapes/cubes/Cube.cpp
        src/shapes/cubes/Cube.h
        src/shapes/cylinders/Cylinder.cpp
        src/shapes/cylinders/Cylinder.h
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
        tests/plane_tests.cpp
        tests/patterns_tests.cpp
        tests/cubes_tests.cpp
        tests/cylinders_tests.cpp
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
add_executable(RealShadows exercises/RealShadows.cpp)
target_link_libraries(RealShadows PRIVATE rtc_core)
add_executable(FirstPlane exercises/FirstPlane.cpp)
target_link_libraries(FirstPlane PRIVATE rtc_core)
add_executable(FirstPattern exercises/FirstPattern.cpp)
target_link_libraries(FirstPattern PRIVATE rtc_core)
add_executable(NestedPatternExamples exercises/NestedPatternExamples.cpp)
target_link_libraries(NestedPatternExamples PRIVATE rtc_core)
add_executable(FirstReflection exercises/FirstReflection.cpp)
target_link_libraries(FirstReflection PRIVATE rtc_core)
add_executable(FirstRefraction exercises/FirstRefraction.cpp)
target_link_libraries(FirstRefraction PRIVATE rtc_core)
add_executable(FirstCubes exercises/FirstCubes.cpp)
target_link_libraries(FirstCubes PRIVATE rtc_core)
add_executable(CoverImage exercises/CoverImage.cpp)
target_link_libraries(CoverImage PRIVATE rtc_core)