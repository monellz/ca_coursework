find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
add_executable(parse_test parse_test.cc)
add_executable(bitset_test bitset_test.cc)
add_executable(replace_policy_test replace_policy_test.cc)


target_link_libraries(parse_test
    ${GTEST_BOTH_LIBRARIES}
    pthread
    file_parser
)
target_link_libraries(bitset_test
    ${GTEST_BOTH_LIBRARIES}
    pthread
)
target_link_libraries(replace_policy_test
    ${GTEST_BOTH_LIBRARIES}
    pthread
    cache_simulator
)

add_test(NAME parse_test COMMAND parse_test)
add_test(NAME bitset_test COMMAND bitset_test)
add_test(NAME replace_policy_test COMMAND replace_policy_test)
