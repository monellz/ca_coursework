find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})
add_executable(parse_test parse_test.cc)


target_link_libraries(parse_test
    ${GTEST_BOTH_LIBRARIES}
    pthread
    file_parser
)

gtest_discover_tests(parse_test)
