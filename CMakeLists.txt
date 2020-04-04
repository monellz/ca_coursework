cmake_minimum_required(VERSION 3.10)
project(cache_simulator)

add_compile_options(-O3)

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

enable_testing()
add_subdirectory(test)
