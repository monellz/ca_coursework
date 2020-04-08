add_library(bench_manager STATIC bench_manager.cc)
target_link_libraries(
    bench_manager
    file_parser
)

add_executable(write_policy_bench write_policy_bench.cc)
add_executable(replace_policy_bench replace_policy_bench.cc)
add_executable(cache_layout_bench cache_layout_bench.cc)
add_executable(bip_bench bip_bench.cc)
add_executable(score_init_bench score_init_bench.cc)
add_executable(score_threshold_bench score_threshold_bench.cc)
add_executable(log_bench log_bench.cc)
target_link_libraries(
    write_policy_bench
    cache
    bench_manager
)
target_link_libraries(
    replace_policy_bench
    cache
    bench_manager
)
target_link_libraries(
    cache_layout_bench
    cache
    bench_manager
)
target_link_libraries(
    bip_bench
    cache
    bench_manager
)
target_link_libraries(
    score_init_bench
    cache
    bench_manager
)
target_link_libraries(
    score_threshold_bench
    cache
    bench_manager
)
target_link_libraries(
    log_bench
    cache
    bench_manager
)



