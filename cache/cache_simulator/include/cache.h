#ifndef CACHE_H_
#define CACHE_H_
#include "cache_util.h"

namespace cache {

struct CacheLayout {
    int way;
    int block_size; //byte
    int total_size; //byte
};

class Cache {
public:
    CacheLayout layout;
    virtual void 
}
} //namespace cache

#endif //CACHE_H_
