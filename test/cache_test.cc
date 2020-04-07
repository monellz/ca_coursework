#include <gtest/gtest.h>
#include <stdlib.h>
#include <iostream>

#include "cache.h"
using namespace cache;

TEST(cache_test, lru_read) {
    const unsigned BLOCK = 2; // 4 bytes
    const unsigned INDEX = 2; //4 groups
    const unsigned TAG = 60;
    const unsigned WAY = 4;

    CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, LRU<WAY>> lru_cache(WriteAllocate::Yes);

    Access ac;
    ac.type = Read;
    ac.addr = 0;    


    for (int i = 0; i < 64; i += 4) {
        ac.addr = i;
        EXPECT_FALSE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 1;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 2;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 3;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
    }
    EXPECT_EQ(PerfStats::get_instance().total_access, 64);
    EXPECT_EQ(PerfStats::get_instance().cache_miss, 16);
    EXPECT_EQ(PerfStats::get_instance().memory_access, 16);
    PerfStats::get_instance().clear();

    for (int i = 0; i < 64; i += 4) {
        ac.addr = i;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 1;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 2;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 3;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
    }
    EXPECT_EQ(PerfStats::get_instance().total_access, 64);
    EXPECT_EQ(PerfStats::get_instance().cache_miss, 0);
    EXPECT_EQ(PerfStats::get_instance().memory_access, 0);
    PerfStats::get_instance().clear();
}


TEST(cache_test, lru_write_back) {
    const unsigned BLOCK = 2; // 4 bytes
    const unsigned INDEX = 2; //4 groups
    const unsigned TAG = 60;
    const unsigned WAY = 4;

    CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, LRU<WAY>> lru_cache(WriteAllocate::Yes);

    Access ac;
    ac.type = Write;
    ac.addr = 0;    

    for (int i = 0; i < 64; i += 4) {
        ac.addr = i;
        EXPECT_FALSE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 1;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 2;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 3;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
    }
    EXPECT_EQ(PerfStats::get_instance().total_access, 64);
    EXPECT_EQ(PerfStats::get_instance().cache_miss, 16);
    EXPECT_EQ(PerfStats::get_instance().memory_access, 16);
    PerfStats::get_instance().clear();

    for (int i = 0; i < 64; i += 4) {
        ac.addr = i;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 1;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 2;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 3;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
    }
    EXPECT_EQ(PerfStats::get_instance().total_access, 64);
    EXPECT_EQ(PerfStats::get_instance().cache_miss, 0);
    EXPECT_EQ(PerfStats::get_instance().memory_access, 0);
    PerfStats::get_instance().clear();


    for (int i = 64; i < 128; i += 4) {
        ac.addr = i;
        EXPECT_FALSE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 1;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 2;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 3;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
    }
    EXPECT_EQ(PerfStats::get_instance().total_access, 64);
    EXPECT_EQ(PerfStats::get_instance().cache_miss, 16);
    EXPECT_EQ(PerfStats::get_instance().memory_access, 32);
    PerfStats::get_instance().clear();

}

TEST(cache_test, lru_write_through) {
    const unsigned BLOCK = 2; // 4 bytes
    const unsigned INDEX = 2; //4 groups
    const unsigned TAG = 60;
    const unsigned WAY = 4;

    CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteThrough<TAG>, LRU<WAY>> lru_cache(WriteAllocate::Yes);

    Access ac;
    ac.type = Write;
    ac.addr = 0;    

    for (int i = 0; i < 64; i += 4) {
        ac.addr = i;
        EXPECT_FALSE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 1;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 2;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 3;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
    }
    EXPECT_EQ(PerfStats::get_instance().total_access, 64);
    EXPECT_EQ(PerfStats::get_instance().cache_miss, 16);
    EXPECT_EQ(PerfStats::get_instance().memory_access, (2 + 1 + 1 + 1) * 16);
    PerfStats::get_instance().clear();
}

TEST(cache_test, lru_no_allocate) {
    const unsigned BLOCK = 2; // 4 bytes
    const unsigned INDEX = 2; //4 groups
    const unsigned TAG = 60;
    const unsigned WAY = 4;

    CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, LRU<WAY>> wb_cache(WriteAllocate::No);
    CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteThrough<TAG>, LRU<WAY>> wt_cache(WriteAllocate::No);

    Access ac;
    ac.type = Write;
    ac.addr = 0;    

    for (int i = 0; i < 64; i += 4) {
        ac.addr = i;
        EXPECT_FALSE(wb_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 1;
        EXPECT_FALSE(wb_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 2;
        EXPECT_FALSE(wb_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 3;
        EXPECT_FALSE(wb_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
    }
    EXPECT_EQ(PerfStats::get_instance().total_access, 64);
    EXPECT_EQ(PerfStats::get_instance().cache_miss, 64);
    EXPECT_EQ(PerfStats::get_instance().memory_access, 64);
    PerfStats::get_instance().clear();


    for (int i = 0; i < 64; i += 4) {
        ac.addr = i;
        EXPECT_FALSE(wt_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 1;
        EXPECT_FALSE(wt_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 2;
        EXPECT_FALSE(wt_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 3;
        EXPECT_FALSE(wt_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
    }
    EXPECT_EQ(PerfStats::get_instance().total_access, 64);
    EXPECT_EQ(PerfStats::get_instance().cache_miss, 64);
    EXPECT_EQ(PerfStats::get_instance().memory_access, 64);
    PerfStats::get_instance().clear();

}

TEST(cache_test, lru_all_associate) {
    const unsigned BLOCK = 2; // 4 bytes
    const unsigned INDEX = 1; //1 groups -> associate
    const unsigned TAG = 61;
    const unsigned WAY = 4;

    CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, LRU<WAY>> lru_cache(WriteAllocate::Yes);

    Access ac;
    ac.type = Write;
    ac.addr = 0;    

    for (int i = 0; i < 16; i += 4) {
        ac.addr = i;
        EXPECT_FALSE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 1;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 2;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 3;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
    }
    EXPECT_EQ(PerfStats::get_instance().total_access, 16);
    EXPECT_EQ(PerfStats::get_instance().cache_miss, 4);
    EXPECT_EQ(PerfStats::get_instance().memory_access, 4);
    PerfStats::get_instance().clear();

    for (int i = 0; i < 16; i += 4) {
        ac.addr = i;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 1;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 2;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 3;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
    }
    EXPECT_EQ(PerfStats::get_instance().total_access, 16);
    EXPECT_EQ(PerfStats::get_instance().cache_miss, 0);
    EXPECT_EQ(PerfStats::get_instance().memory_access, 0);
    PerfStats::get_instance().clear();


    for (int i = 16; i < 32; i += 4) {
        ac.addr = i;
        EXPECT_FALSE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 1;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 2;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
        ac.addr = i + 3;
        EXPECT_TRUE(lru_cache.access(ac)) << "i: " << i << " addr: " << ac.addr;
    }
    EXPECT_EQ(PerfStats::get_instance().total_access, 16);
    EXPECT_EQ(PerfStats::get_instance().cache_miss, 4);
    EXPECT_EQ(PerfStats::get_instance().memory_access, 4);
    PerfStats::get_instance().clear();

}