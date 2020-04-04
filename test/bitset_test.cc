#include <gtest/gtest.h>
#include <stdlib.h>
#include <iostream>
#include "bitset.h"

TEST(bitset_test, compile_log) {
    EXPECT_EQ(CEIL_LOG2(1), 0);
    EXPECT_EQ(CEIL_LOG2(2), 1);
    EXPECT_EQ(CEIL_LOG2(3), 2);
    EXPECT_EQ(CEIL_LOG2(4), 2);
    EXPECT_EQ(CEIL_LOG2(5), 3);
    EXPECT_EQ(CEIL_LOG2(6), 3);
    EXPECT_EQ(CEIL_LOG2(7), 3);
    EXPECT_EQ(CEIL_LOG2(8), 3);
    EXPECT_EQ(CEIL_LOG2(9), 4);
    EXPECT_EQ(CEIL_LOG2(10), 4);
    EXPECT_EQ(CEIL_LOG2(16), 4);
    EXPECT_EQ(CEIL_LOG2(17), 5);
}


TEST(bitset_test, single_bit_op) {
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


TEST(bitset_test, range_op) {
    Bitset<100> bs;
    EXPECT_EQ(bs.size(), 100);
    bs.range_set(0, 8, 111);
    EXPECT_EQ(bs.range_get(0, 8), 111);

    bs.range_set(7, 9, 3);
    EXPECT_EQ(bs.range_get(7, 9), 3);

    bs.range_set(7, 9, 2);
    EXPECT_EQ(bs.range_get(7, 9), 2);

    bs.range_set(0, 15, 22222);
    EXPECT_EQ(bs.range_get(0, 15), 22222);

    std::cout << "rand set" << std::endl;

    int count = 1000;
    for (int i = 0; i < count; ++i) {
        int s = rand() % 100;
        int e = rand() % 100;
        if (s == e) continue;
        if (s > e) {
            int t = s;
            s = e;
            e = t;
        }

        unsigned int value = rand() % (1 << (e - s));
        bs.range_set(s, e, value);
        EXPECT_EQ(bs.range_get(s, e), value);
    }
}
