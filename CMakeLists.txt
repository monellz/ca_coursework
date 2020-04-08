cmake_minimum_required(VERSION 3.5)
project(cache_simulator)

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++14")
find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
    message("openmp found")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

configure_file(
    ${PROJECT_SOURCE_DIR}/include/global_build_config.h.in
    ${PROJECT_SOURCE_DIR}/include/global_build_config.h
    @ONLY
)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/file_parser/include)
include_directories(${PROJECT_SOURCE_DIR}/cache/include)

add_subdirectory(cache)
add_subdirectory(file_parser)
add_subdirectory(bench)

find_package(GTest COMPONENTS)
if (GTEST_FOUND)
    message("gtest found")
    include_directories(${GTEST_INCLUDE_DIRS})
    enable_testing()
    add_subdirectory(test)
endif()

