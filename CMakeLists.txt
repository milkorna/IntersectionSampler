cmake_minimum_required(VERSION 3.16)

project(IntersectionSampler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(IntersectionSampler
    src/main.cpp

    src/Common/Direction3D.cpp
    src/Common/Plane.cpp
    src/Common/Point3D.cpp
    src/Common/Vector3D.cpp
    src/Common/Cone.cpp
    src/Common/Cylinder.cpp

    src/IO/DataReader.cpp
    src/IO/DataWriter.cpp

    src/IntersectionPointSampler.cpp
    src/IntersectionPointSamplerFactory.cpp
    src/PlanePointSampler.cpp
    src/SamplingUtils.cpp
    src/ShapePointSampler.cpp
)

target_include_directories(IntersectionSampler PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
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