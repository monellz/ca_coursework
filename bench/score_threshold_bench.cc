#include <iostream>
#include <string>
#include <cstdio>
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

    PerfStats& perf = PerfStats::get_instance();
    for (int i = 0; i < manager.benches.size(); ++i) {
        CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, Score<WAY, 0, 0>> s0_cache(WriteAllocate::Yes);
        CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, Score<WAY, 0, 16>> s16_cache(WriteAllocate::Yes);
        CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, Score<WAY, 0, 32>> s32_cache(WriteAllocate::Yes);
        CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, Score<WAY, 0, 48>> s48_cache(WriteAllocate::Yes);
        CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, Score<WAY, 0, 64>> s64_cache(WriteAllocate::Yes);
        CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, LRU<WAY>> lru_cache(WriteAllocate::Yes);

        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            lru_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [lru_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();

        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            s0_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [s0_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();

        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            s16_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [s16_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();

        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            s32_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [s32_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();

        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            s48_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [s48_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();

        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            s64_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [s64_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();
    }

    return 0;
}