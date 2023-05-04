cmake_minimum_required(VERSION 3.0.0)
project(BowlingKata)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif ()

add_library(BowlingKata STATIC)
target_compile_features(BowlingKata PRIVATE cxx_std_17)

file(GLOB_RECURSE BOWLING_SRC include/*.h src/*.cpp)

target_sources(BowlingKata PRIVATE ${BOWLING_SRC})
target_include_directories(BowlingKata PUBLIC include/)

add_subdirectory(test/)
