#ifndef CACHE_UTIL_H_
#define CACHE_UTIL_H_

#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <atomic>
#include <iostream>
#include "omp.h"
#include "perf_stats.h"

namespace cache {

enum AccessType {
    Read,
    Write
};

struct Access {
    AccessType type;
    uint64_t addr;
};

}; //namespace cache

#endif //CACHE_UTIL_H_
