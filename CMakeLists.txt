cmake_minimum_required(VERSION 3.16)

project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(IntersectionSampler
    src/CommonTypes.cpp
    src/DataReader.cpp
    src/IntersectionPointSampler.cpp
    src/main.cpp
    src/Plane.cpp
    src/DataWriter.cpp
    src/PlanePointSampler.cpp
    src/ShapePointSampler.cpp
    src/Shapes.cpp
    src/SamplingUtils.cpp
)

if (MSVC)
    target_compile_options(IntersectionSampler PRIVATE
        /W4
        /permissive-
    )
else()
    target_compile_options(IntersectionSampler PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wshadow
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Wnull-dereference
        -Wdouble-promotion
        -Wformat=2
    )
endif()