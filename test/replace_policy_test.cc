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
        lru_cache.victim_after_access(i);
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

    EXPECT_EQ(lru_cache.victim_after_access(0), 1);    
    EXPECT_EQ(lru_cache.victim_after_access(1), 2);    
    EXPECT_EQ(lru_cache.victim_after_access(2), 3);    
    EXPECT_EQ(lru_cache.victim_after_access(3), 4);    
    EXPECT_EQ(lru_cache.victim_after_access(4), 5);    
    EXPECT_EQ(lru_cache.victim_after_access(5), 6);    
    EXPECT_EQ(lru_cache.victim_after_access(6), 7);    

    EXPECT_EQ(lru_cache.victim_after_access(7), 0);
    EXPECT_EQ(lru_cache.victim_after_access(6), 0);
    EXPECT_EQ(lru_cache.victim_after_access(5), 0);
}


TEST(replace_policy_test, bt) {


}
