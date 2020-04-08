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
        CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, LRU<WAY>> lru_cache(WriteAllocate::Yes);
        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            lru_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [lru_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();

        CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, Rand<WAY>> rand_cache(WriteAllocate::Yes);
        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            rand_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [rand_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();

        CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, BT<WAY>> bt_cache(WriteAllocate::Yes);
        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            bt_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [bt_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();

        CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, FIFO<WAY>> fifo_cache(WriteAllocate::Yes);
        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            fifo_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [fifo_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();

        CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, LIP<WAY>> lip_cache(WriteAllocate::Yes);
        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            lip_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [lip_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();

        CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, BIP<WAY>> bip_cache(WriteAllocate::Yes);
        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            bip_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [bip_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();

        CacheSimulator<TAG, INDEX, BLOCK, WAY, WriteBack<TAG>, Score<WAY>> score_cache(WriteAllocate::Yes);
        for (int j = 0; j < manager.benches[i].access.size(); ++j) {
            score_cache.access(manager.benches[i].access[j]);
        }
        printf("[%s] [score_cache] cache_miss: %d/%d=%f\n", manager.benches[i].name.c_str(), perf.cache_miss, perf.total_access, (float)perf.cache_miss / perf.total_access);
        perf.clear();
    }
}