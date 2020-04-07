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
        CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, BIP<WAY, 2>> p2_cache(WriteAllocate::Yes);
        CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, BIP<WAY, 4>> p4_cache(WriteAllocate::Yes);
        CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, BIP<WAY, 8>> p8_cache(WriteAllocate::Yes);
        CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, BIP<WAY, 16>> p16_cache(WriteAllocate::Yes);
        CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, LRU<WAY>> lru_cache(WriteAllocate::Yes);

        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            lru_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [lru_cache] lru_cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();

        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            p2_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [p2_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();

        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            p4_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [p4_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();

        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            p8_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [p8_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();

        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            p16_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [p16_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();
    }
    return 0;
}