#include <gtest/gtest.h>
#include <stdlib.h>
#include <iostream>

#include "way_metadata.h"


using namespace cache;

TEST(way_metadata_test, write_back) {
    const unsigned int TAG_NUM = 20;
    WriteBack<TAG_NUM> wb;
    EXPECT_FALSE(wb.is_valid());
    EXPECT_FALSE(wb.is_dirty());
    

    for (int i = 0; i < 1000; ++i) {
        unsigned int tag = rand() % (1 << TAG_NUM);
        wb.set_tag(tag);
        EXPECT_EQ(wb.get_tag(), tag);
    }

    wb.write_access();
    EXPECT_TRUE(wb.is_dirty());

    wb.before_swap_out();
    EXPECT_FALSE(wb.is_dirty());
}

TEST(way_metadata_test, write_through) {
    const unsigned int TAG_NUM = 20;
    WriteThrough<TAG_NUM> wt;
    EXPECT_FALSE(wt.is_valid());

    for (int i = 0; i < 1000; ++i) {
        unsigned int tag = rand() % (1 << TAG_NUM);
        wt.set_tag(tag);
        EXPECT_EQ(wt.get_tag(), tag);
    }
}
