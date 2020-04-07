cmake_minimum_required(VERSION 3.10)
project(cache_simulator)

add_compile_options(-O3)
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

enable_testing()
add_subdirectory(test)
