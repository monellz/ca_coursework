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
    CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, LRU<WAY>> wb_alloc_cache(WriteAllocate::Yes);
    CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, LRU<WAY>> wb_nalloc_cache(WriteAllocate::No);
    CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteThrough<TAG>, LRU<WAY>> wt_alloc_cache(WriteAllocate::Yes);
    CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteThrough<TAG>, LRU<WAY>> wt_nalloc_cache(WriteAllocate::No);

    PerfStats& perf = PerfStats::get_instance();
    for (int i = 0; i < manager.benches.size(); ++i) {
        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            wb_alloc_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [wb_alloc_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();

        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            wb_nalloc_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [wb_nalloc_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();

        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            wt_alloc_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [wt_alloc_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();

        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            wt_nalloc_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [wt_nalloc_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();
    }
}