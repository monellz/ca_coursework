#include <iostream>
#include <string>
#include "cache.h"
#include "include/bench_manager.h"

using namespace std;
using namespace cache;

/*
 *  CACHE: 128KB
 *  BLOCK_SIZE: 8B
 *  WAY: 8
 *  REPLACEMENT_POLICY: LRU 
 *  
 *  BLOCK_NUM:  128KB / 8B = 2^{14}
 *  INDEX_BIT:  11
 *  TAG_BIT:    50
 * 
 */
const int TAG = 50;
const int INDEX = 11;
const int BLOCK = 3;
const int WAY = 8;

bench::BenchManager manager;

int main() {
    //CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, LRU<WAY>> lru_cache(WriteAllocate::Yes);
    PerfStats& perf = PerfStats::get_instance();

    /*
    //8B BLOCK_SIZE, Directly mapping
    for (int i = 0; i < manager.benches.size(); ++i) {
        CacheSimulator<47, 14, 3, 1, WriteBack<47>, ReplacePolicy<1>> d_8_cache(WriteAllocate::Yes);
        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            d_8_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [8B_direct_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();
    }
    std::cout << std::endl;
    */


    //8B BLOCK_SIZE, all associate
    for (int i = 0; i < manager.benches.size(); ++i) {
        CacheSimulator<61, 0, 3, (1 << 14), WriteBack<61>, LRU<(1 << 14)>> a_8_cache(WriteAllocate::Yes);
        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            a_8_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [8B_all_associate_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();
    }
    std::cout << std::endl;

    /*
    //8B BLOCK_SIZE, 4 way
    for (int i = 0; i < manager.benches.size(); ++i) {
        CacheSimulator<49, 12, 3, 4, WriteBack<49>, LRU<4>> w4_8_cache(WriteAllocate::Yes);
        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            w4_8_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [8B_4way_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();
    }
    std::cout << std::endl;

    //8B BLOCK_SIZE, 8 way
    for (int i = 0; i < manager.benches.size(); ++i) {
        CacheSimulator<50, 11, 3, 8, WriteBack<50>, LRU<8>> w8_8_cache(WriteAllocate::Yes);
        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            w8_8_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [8B_8way_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();
    }
    std::cout << std::endl;

    //32B BLOCK_SIZE, Directly mapping
    for (int i = 0; i < manager.benches.size(); ++i) {
        CacheSimulator<47, 12, 5, 1, WriteBack<47>, ReplacePolicy<1>> d_32_cache(WriteAllocate::Yes);
        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            d_32_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [32B_direct_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();
    }
    std::cout << std::endl;
    */

    //32B BLOCK_SIZE, all associate
    for (int i = 0; i < manager.benches.size(); ++i) {
        CacheSimulator<59, 0, 5, (1 << 12), WriteBack<59>, LRU<(1 << 12)>> a_32_cache(WriteAllocate::Yes);
        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            a_32_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [32B_all_associate_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();
    }
    std::cout << std::endl;
    /*
    //32B BLOCK_SIZE, 4 way
    for (int i = 0; i < manager.benches.size(); ++i) {
        CacheSimulator<49, 10, 5, 4, WriteBack<49>, LRU<4>> w4_32_cache(WriteAllocate::Yes);
        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            w4_32_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [32B_4way_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();
    }
    std::cout << std::endl;

    //32B BLOCK_SIZE, 8 way
    for (int i = 0; i < manager.benches.size(); ++i) {
        CacheSimulator<50, 9, 5, 8, WriteBack<50>, LRU<8>> w8_32_cache(WriteAllocate::Yes);
        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            w8_32_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [32B_8way_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();
    }
    std::cout << std::endl;

    //64B BLOCK_SIZE, Directly mapping
    for (int i = 0; i < manager.benches.size(); ++i) {
        CacheSimulator<47, 11, 6, 1, WriteBack<47>, ReplacePolicy<1>> d_64_cache(WriteAllocate::Yes);
        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            d_64_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [64B_direct_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();
    }
    std::cout << std::endl;
    */

    //64B BLOCK_SIZE, all associate
    for (int i = 0; i < manager.benches.size(); ++i) {
        CacheSimulator<58, 0, 6, (1 << 11), WriteBack<58>, LRU<(1 << 11)>> a_64_cache(WriteAllocate::Yes);
        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            a_64_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [64B_all_associate_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();
    }
    std::cout << std::endl;
    /*

    //64B BLOCK_SIZE, 4 way
    for (int i = 0; i < manager.benches.size(); ++i) {
        CacheSimulator<49, 9, 6, 4, WriteBack<49>, LRU<4>> w4_64_cache(WriteAllocate::Yes);
        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            w4_64_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [64B_4way_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();
    }
    std::cout << std::endl;

    //64B BLOCK_SIZE, 8 way
    for (int i = 0; i < manager.benches.size(); ++i) {
        CacheSimulator<50, 8, 6, 8, WriteBack<50>, LRU<8>> w8_64_cache(WriteAllocate::Yes);
        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            w8_64_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [64B_8way_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();
    }
    std::cout << std::endl;

    */

}