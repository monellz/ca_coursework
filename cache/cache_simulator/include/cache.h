#ifndef CACHE_H_
#define CACHE_H_
#include "cache_util.h"

namespace cache {

template<unsigned int WAY, unsigned int BLOCK_SIZE, unsigned int TOTAL_SIZE>
class Cache {
public:
    CacheLayout layout;
};
} //namespace cache

#endif //CACHE_H_
