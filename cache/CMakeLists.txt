cmake_minimum_required(VERSION 3.10)
project(cache)

configure_file(
    ${PROJECT_SOURCE_DIR}/include/global_build_config.h.in
    ${PROJECT_SOURCE_DIR}/include/global_build_config.h.in
    @ONLY
)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/file_parser/include)
include_directories(${PROJECT_SOURCE_DIR}/cache_simulator/include)

add_subdirectory(file_parser)

enable_testing()
add_subdirectory(test)
