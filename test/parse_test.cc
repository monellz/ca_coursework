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
}

TEST(parse_64_blankline_test, bodytrack_1m) {
    FileParser parser(None);
    string path = string(GLOBAL_PROJECT_DIR) + "/trace" + "/bodytrack_1m.trace";
    vector<cache::Access> access_list;
    EXPECT_TRUE(parser.parse(path, access_list)) << "parse error";
    EXPECT_EQ(access_list.size(), 290546) << "trace num is not correct";
}
TEST(parse_rw_64_test, bzip2) {
    FileParser parser(ReadWrite);
    string path = string(GLOBAL_PROJECT_DIR) + "/trace" + "/bzip2.trace";
    vector<cache::Access> access_list;
    EXPECT_TRUE(parser.parse(path, access_list)) << "parse error";
    EXPECT_EQ(access_list.size(), 544514) << "trace num is not correct";

}
TEST(parse_64_blankline_test, canneal_uniq) {
    FileParser parser(None);
    string path = string(GLOBAL_PROJECT_DIR) + "/trace" + "/canneal.uniq.trace";
    vector<cache::Access> access_list;
    EXPECT_TRUE(parser.parse(path, access_list)) << "parse error";
    EXPECT_EQ(access_list.size(), 548918) << "trace num is not correct";

}
TEST(parse_ls_64_test, gcc) {
    FileParser parser(LoadStore);
    string path = string(GLOBAL_PROJECT_DIR) + "/trace" + "/gcc.trace";
    vector<cache::Access> access_list;
    EXPECT_TRUE(parser.parse(path, access_list)) << "parse error";
    EXPECT_EQ(access_list.size(), 515683) << "trace num is not correct";

}
TEST(parse_rw_64_test, mcf) {
    FileParser parser(ReadWrite);
    string path = string(GLOBAL_PROJECT_DIR) + "/trace" + "/mcf.trace";
    vector<cache::Access> access_list;
    EXPECT_TRUE(parser.parse(path, access_list)) << "parse error";
    EXPECT_EQ(access_list.size(), 507700) << "trace num is not correct";

}
TEST(parse_rw_64_test, perlbench) {
    FileParser parser(ReadWrite);
    string path = string(GLOBAL_PROJECT_DIR) + "/trace" + "/perlbench.trace";
    vector<cache::Access> access_list;
    EXPECT_TRUE(parser.parse(path, access_list)) << "parse error";
    EXPECT_EQ(access_list.size(), 507441) << "trace num is not correct";

}
TEST(parse_64_blankline_test, streamcluster) {
    FileParser parser(None);
    string path = string(GLOBAL_PROJECT_DIR) + "/trace" + "/streamcluster.trace";
    vector<cache::Access> access_list;
    EXPECT_TRUE(parser.parse(path, access_list)) << "parse error";
    EXPECT_EQ(access_list.size(), 986159) << "trace num is not correct";

}
TEST(parse_ls_64_test, swim) {
    FileParser parser(LoadStore);
    string path = string(GLOBAL_PROJECT_DIR) + "/trace" + "/swim.trace";
    vector<cache::Access> access_list;
    EXPECT_TRUE(parser.parse(path, access_list)) << "parse error";
    EXPECT_EQ(access_list.size(), 303193) << "trace num is not correct";

}
TEST(parse_ls_64_test, twolf) {
    FileParser parser(LoadStore);
    string path = string(GLOBAL_PROJECT_DIR) + "/trace" + "/twolf.trace";
    vector<cache::Access> access_list;
    EXPECT_TRUE(parser.parse(path, access_list)) << "parse error";
    EXPECT_EQ(access_list.size(), 482824) << "trace num is not correct";
}
