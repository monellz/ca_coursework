add_library(bench_manager STATIC bench_manager.cc)
target_link_libraries(
    bench_manager
    file_parser
)

add_executable(write_policy_bench write_policy_bench.cc)
target_link_libraries(
    write_policy_bench
    cache
    bench_manager
)