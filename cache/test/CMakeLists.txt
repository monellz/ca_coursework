find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
add_executable(parse_test parse_test.cc)
add_executable(bitset_test bitset_test.cc)


target_link_libraries(parse_test
    ${GTEST_BOTH_LIBRARIES}
    pthread
    file_parser
)
target_link_libraries(bitset_test
    ${GTEST_BOTH_LIBRARIES}
    pthread
)

add_test(NAME parse_test COMMAND parse_test)
add_test(NAME bitset_test COMMAND bitset_test)
