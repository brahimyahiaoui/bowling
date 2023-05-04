cmake_minimum_required(VERSION 3.0.0)
project(BowlingKata_Tests)

add_executable(BowlingKata_Tests)
target_compile_features(BowlingKata_Tests PRIVATE cxx_std_17)

enable_testing()

file(GLOB_RECURSE BOWLING_TESTS_SRC *.cpp)

target_sources(BowlingKata_Tests PRIVATE ${BOWLING_TESTS_SRC})
target_include_directories(
    BowlingKata_Tests

    PRIVATE

    ${CMAKE_HOME_DIRECTORY}/3rdparty/gtest/googletest-master/googletest/include/
    ${CMAKE_HOME_DIRECTORY}/3rdparty/gtest/googletest-master/googlemock/include/
)

# Create the executable into the binary directory
set_target_properties(BowlingKata_Tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/")

# Forcing GTest to be built as a shared library
set(BUILD_GTEST ON CACHE BOOL "")
set(BUILD_SHARED_LIBS ON CACHE BOOL "")

add_subdirectory("${CMAKE_HOME_DIRECTORY}/3rdparty/gtest/googletest-master/" "${CMAKE_BINARY_DIR}/gtest/")

# Forcing GTest's DLLs to be built into the binary directory, beside the executable
set_target_properties(gtest PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/")
set_target_properties(gtest_main PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/")
set_target_properties(gmock PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/")
set_target_properties(gmock_main PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/")

target_link_libraries(BowlingKata_Tests PRIVATE BowlingKata gtest gtest_main)

add_test(BowlingKata_Tests BowlingKata_Tests)
