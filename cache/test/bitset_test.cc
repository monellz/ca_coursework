#include <gtest/gtest.h>
#include "bitset.h"


TEST(bitset_test, bitset) {
    Bitset<100> bs;
    for (int i = 0; i < bs.size(); ++i) {
        EXPECT_FALSE(bs.test(i));
    }
    bs.set();
    for (int i = 0; i < bs.size(); ++i) {
        EXPECT_TRUE(bs.test(i));
    }
    bs.reset();
    for (int i = 0; i < bs.size(); ++i) {
        bs.set(i);
        EXPECT_TRUE(bs.test(i));
        bs.reset(i);
        EXPECT_FALSE(bs.test(i));
    }
}
