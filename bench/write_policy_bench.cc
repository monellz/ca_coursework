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
}