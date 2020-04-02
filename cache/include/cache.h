#ifndef CACHE_H_
#define CACHE_H_
#include "cache_util.h"

//write back / write through
#include "way_metadata.h"
//lru / bt
#include "replace_policy.h"

namespace cache {

enum WriteAllocate {
    Yes,
    No
};

template<unsigned GROUP, unsigned WAY, unsigned TAG, typename WRITE_POLICY, typename REPLACE_POLICY>
class CacheSimulator {
private:
    WayMetadata<TAG>* way_metadata[GROUP][WAY];
    ReplacePolicy<WAY>* policy[GROUP];
    WriteAllocate write_allocate_type;
public:
    CacheSimulator(WriteAllocate type): write_allocate_type(type) {
        for (int i = 0; i < GROUP; ++i) {
            for (int j = 0; j < WAY; ++j) {
                way_metadata[i][j] = new WRITE_POLICY();
            }

            policy[i] = new REPLACE_POLICY();
        }
    }

    ~CacheSimulator() {
        for (int i = 0; i < GROUP; ++i) {
            for (int j = 0; j < WAY; ++j) {
                delete way_metadata[i][j];
            }

            delete policy[i];
        }
    }

    bool access(const Access& ac) {
        bool miss = false;
        unsigned int index;
        unsigned int tag;

        if (ac.type == Read) {
            miss = read(ac.addr);
        } else {
            assert(ac.type == Write);
            miss = write(ac.addr);
        }

        if (miss) {
            auto stats = PerfStats::get_instance();
            stats.cache_miss++;
        }
        return miss;
    }

    bool read(unsigned int tag, unsigned int index) {
        for (int i = 0; i < WAY; ++i) {
            if (way_metadata[index][i].get_tag() == tag) {
                //cache hit
                
                //access the way: 
                //  replace_policy update
                policy[index].access(i);
                return true;
            }
        }

        //cache miss
        
        //find the victim way by the policy
        int victim = policy[index].victim();

        //swap out the victim block to memory
        way_metadata[index][victim].before_swap_out();

        //fetch block from memory:
        //  update the tag and valid
        way_metadata[index][victim].set_tag(tag);
        way_metadata[index][victim].set_valid();

        //access the way to get the data block:
        //  replace_policy update
        policy[index].access(victim);


        return false;
    }

    bool write(unsigned int tag, unsigned int index) {
        for (int i = 0; i < WAY; ++i) {
            if (way_metadata[index][i].is_valid() && way_metadata[index][i].get_tag() == tag) {
                //cache hit
                                                
                //access the way:
                //  replace_policy update
                //  metadata update
                policy[index].access(i);
                way_metadata[index][i].write_access();
                return true;
            }
        }

        //cache miss
        
        if (write_allocate_type == Yes) {
            //find the victim way by the policy
            int victim = policy[index].victim();

            //swap out the victim block to memory
            way_metadata[index][victim].before_swap_out();

            //fetch block from memory:
            //  update the tag and valid
            way_metadata[index][victim].set_tag(tag);
            way_metadata[index][victim].set_valid();

            //access the way to write the data block
            //  replace_policy update
            //  set dirty
            policy[index].access(victim);
            way_metadata[index][victim].set_dirty();
        } else {
            assert(write_allocate_type == No);
            //directly write it to memory
            
            //TODO: STAT
        }
        
        return false;
    }
};

}; //namespace cache

#endif //CACHE_H_
