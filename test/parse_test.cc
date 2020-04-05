#include <gtest/gtest.h>
#include "cache_util.h"
#include "file_parser.h"
#include "global_build_config.h"

using namespace file;
using namespace std;


TEST(parse_rw_64_test, astar) {
    FileParser parser(ReadWrite);
    string path = string(GLOBAL_PROJECT_DIR) + "/trace" + "/astar.trace";
    vector<cache::Access> access_list;
    EXPECT_TRUE(parser.parse(path, access_list)) << "parse error";
    EXPECT_EQ(access_list.size(), 501468) << "trace num is not correct";
    EXPECT_EQ(access_list[0].addr, 0x7fe8d76f8bc8);
    EXPECT_EQ(access_list[access_list.size() - 1].addr, 0x7fffbbd83f60);
}

TEST(parse_64_blankline_test, bodytrack_1m) {
    FileParser parser(None);
    string path = string(GLOBAL_PROJECT_DIR) + "/trace" + "/bodytrack_1m.trace";
    vector<cache::Access> access_list;
    EXPECT_TRUE(parser.parse(path, access_list)) << "parse error";
    EXPECT_EQ(access_list.size(), 290546) << "trace num is not correct";
    EXPECT_EQ(access_list[0].addr, 0x1fda39c0);
    EXPECT_EQ(access_list[access_list.size() - 1].addr, 0x1fd074c0);
}
TEST(parse_rw_64_test, bzip2) {
    FileParser parser(ReadWrite);
    string path = string(GLOBAL_PROJECT_DIR) + "/trace" + "/bzip2.trace";
    vector<cache::Access> access_list;
    EXPECT_TRUE(parser.parse(path, access_list)) << "parse error";
    EXPECT_EQ(access_list.size(), 544514) << "trace num is not correct";
    EXPECT_EQ(access_list[0].addr, 0x1a2dce8);
    EXPECT_EQ(access_list[access_list.size() - 1].addr, 0x1a2dc90);
}
TEST(parse_64_blankline_test, canneal_uniq) {
    FileParser parser(None);
    string path = string(GLOBAL_PROJECT_DIR) + "/trace" + "/canneal.uniq.trace";
    vector<cache::Access> access_list;
    EXPECT_TRUE(parser.parse(path, access_list)) << "parse error";
    EXPECT_EQ(access_list.size(), 548918) << "trace num is not correct";
    EXPECT_EQ(access_list[0].addr, 0x1ee59800);
    EXPECT_EQ(access_list[access_list.size() - 1].addr, 0x619c40);
}
TEST(parse_ls_64_test, gcc) {
    FileParser parser(LoadStore);
    string path = string(GLOBAL_PROJECT_DIR) + "/trace" + "/gcc.trace";
    vector<cache::Access> access_list;
    EXPECT_TRUE(parser.parse(path, access_list)) << "parse error";
    EXPECT_EQ(access_list.size(), 515683) << "trace num is not correct";
    EXPECT_EQ(access_list[0].addr, 0x1fffff50);
    EXPECT_EQ(access_list[access_list.size() - 1].addr, 0x1ffff640);
}
TEST(parse_rw_64_test, mcf) {
    FileParser parser(ReadWrite);
    string path = string(GLOBAL_PROJECT_DIR) + "/trace" + "/mcf.trace";
    vector<cache::Access> access_list;
    EXPECT_TRUE(parser.parse(path, access_list)) << "parse error";
    EXPECT_EQ(access_list.size(), 507700) << "trace num is not correct";
    EXPECT_EQ(access_list[0].addr, 0x7fff77885050);
    EXPECT_EQ(access_list[access_list.size() - 1].addr, 0x7fff778852c0);
}
TEST(parse_rw_64_test, perlbench) {
    FileParser parser(ReadWrite);
    string path = string(GLOBAL_PROJECT_DIR) + "/trace" + "/perlbench.trace";
    vector<cache::Access> access_list;
    EXPECT_TRUE(parser.parse(path, access_list)) << "parse error";
    EXPECT_EQ(access_list.size(), 507441) << "trace num is not correct";
    EXPECT_EQ(access_list[0].addr, 0x7fff0d44ee98);
    EXPECT_EQ(access_list[access_list.size() - 1].addr, 0x7fff0d44ee18);
}
TEST(parse_64_blankline_test, streamcluster) {
    FileParser parser(None);
    string path = string(GLOBAL_PROJECT_DIR) + "/trace" + "/streamcluster.trace";
    vector<cache::Access> access_list;
    EXPECT_TRUE(parser.parse(path, access_list)) << "parse error";
    EXPECT_EQ(access_list.size(), 986159) << "trace num is not correct";
    EXPECT_EQ(access_list[0].addr, 0x1fe11a00);
    EXPECT_EQ(access_list[access_list.size() - 1].addr, 0x1f16fa80);
}
TEST(parse_ls_64_test, swim) {
    FileParser parser(LoadStore);
    string path = string(GLOBAL_PROJECT_DIR) + "/trace" + "/swim.trace";
    vector<cache::Access> access_list;
    EXPECT_TRUE(parser.parse(path, access_list)) << "parse error";
    EXPECT_EQ(access_list.size(), 303193) << "trace num is not correct";
    EXPECT_EQ(access_list[0].addr, 0x1fffff78);
    EXPECT_EQ(access_list[access_list.size() - 1].addr, 0x1ffffd18);
}
TEST(parse_ls_64_test, twolf) {
    FileParser parser(LoadStore);
    string path = string(GLOBAL_PROJECT_DIR) + "/trace" + "/twolf.trace";
    vector<cache::Access> access_list;
    EXPECT_TRUE(parser.parse(path, access_list)) << "parse error";
    EXPECT_EQ(access_list.size(), 482824) << "trace num is not correct";
    EXPECT_EQ(access_list[0].addr, 0x1fffff70);
    EXPECT_EQ(access_list[access_list.size() - 1].addr, 0x1fffed48);
}
