#include <gtest/gtest.h>
#include <stdlib.h>
#include <iostream>
#include "replace_policy.h"

using namespace cache;

TEST(replace_policy_test, lru) {
    LRU<8> lru_cache;
    EXPECT_EQ(lru_cache.stack_width(), 3); 
    
    //reset the cache
    for (int i = 0; i < 8; ++i) {
        lru_cache.access(i);
    }

    /*
     * now stack
     *
     * | 7 |
     * -----
     * | 6 |
     * -----
     * | 5 |
     * -----
     * | 4 |
     * -----
     * | 3 |
     * -----
     * | 2 |
     * -----
     * | 1 |
     * -----
     * | 0 |
     * -----
     * -----
     *
     */

    EXPECT_EQ(lru_cache.victim(), 0);    
    lru_cache.access(0);
    EXPECT_EQ(lru_cache.victim(), 1);    
    lru_cache.access(1);
    EXPECT_EQ(lru_cache.victim(), 2);    
    lru_cache.access(2);
    EXPECT_EQ(lru_cache.victim(), 3);    
    lru_cache.access(3);
    EXPECT_EQ(lru_cache.victim(), 4);    
    lru_cache.access(4);
    EXPECT_EQ(lru_cache.victim(), 5);    
    lru_cache.access(5);
    EXPECT_EQ(lru_cache.victim(), 6);    
    lru_cache.access(6);
    EXPECT_EQ(lru_cache.victim(), 7);
    lru_cache.access(7);

    lru_cache.access(1);
    EXPECT_EQ(lru_cache.victim(), 0);
    lru_cache.access(0);
    EXPECT_EQ(lru_cache.victim(), 2);
}


TEST(replace_policy_test, bt) {
    BT<8> bt_cache;
    EXPECT_EQ(bt_cache.victim(), 0);
}
