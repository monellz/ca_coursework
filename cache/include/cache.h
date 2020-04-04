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

template<unsigned TAG, unsigned INDEX, unsigned BLOCK, unsigned WAY, typename WRITE_POLICY, typename REPLACE_POLICY>
class CacheSimulator {
private:
    static const unsigned long long GROUP = 1 << INDEX;
    WayMetadata<TAG>* way_metadata[GROUP][WAY];
    ReplacePolicy<WAY>* policy[GROUP];
    WriteAllocate write_allocate_type;
public:
    CacheSimulator(WriteAllocate type): write_allocate_type(type) {
        assert(TAG + INDEX + BLOCK == 64);
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
        bool hit = false;
        unsigned long long index;
        unsigned long long tag;
        /*
         *  64bit addr
         *  
         *  tag | index | in-block 
         * 
        */
        index = (ac.addr >> BLOCK) % GROUP;
        tag = (ac.addr >> (BLOCK + INDEX)) % (1ull << TAG);
        //std::cout << "index, tag: " << index << ", " << tag << std::endl;
        //std::cout << "addr, GROUP, BLOCK: " << ac.addr << ", " << GROUP << ", " << BLOCK << std::endl;

        if (ac.type == Read) {
            hit = read(tag, index);
        } else {
            assert(ac.type == Write);
            hit = write(tag, index);
        }


        PerfStats::get_instance().forward(hit);
        return hit;
    }

    bool read(unsigned long long tag, unsigned long long index) {
        for (int i = 0; i < WAY; ++i) {
            if (way_metadata[index][i]->is_valid() && way_metadata[index][i]->get_tag() == tag) {
                //cache hit
                
                //access the way: 
                //  cache access
                //  replace_policy update
                PerfStats::get_instance().cache_access++;
                policy[index]->access(i);
                return true;
            }
        }

        //cache miss
        
        //find the victim way by the policy
        int victim = policy[index]->victim();

        //swap out the victim block to memory
        way_metadata[index][victim]->before_swap_out();

        //fetch block from memory:
        //  update the tag and valid
        PerfStats::get_instance().memory_access++;
        way_metadata[index][victim]->set_tag(tag);
        way_metadata[index][victim]->set_valid();

        //access the way to get the data block:
        //  replace_policy update
        PerfStats::get_instance().cache_access++;
        policy[index]->access(victim);

        return false;
    }

    bool write(unsigned long long tag, unsigned long long index) {
        for (int i = 0; i < WAY; ++i) {
            if (way_metadata[index][i]->is_valid() && way_metadata[index][i]->get_tag() == tag) {
                //cache hit
                                                
                //access the way:
                //  replace_policy update
                //  metadata update
                PerfStats::get_instance().cache_access++;
                policy[index]->access(i);
                way_metadata[index][i]->write_access();
                return true;
            }
        }

        //cache miss
        
        if (write_allocate_type == Yes) {
            //find the victim way by the policy
            int victim = policy[index]->victim();

            //swap out the victim block to memory
            way_metadata[index][victim]->before_swap_out();

            //fetch block from memory:
            //  update the tag and valid
            PerfStats::get_instance().memory_access++;
            way_metadata[index][victim]->set_tag(tag);
            way_metadata[index][victim]->set_valid();

            //access the way to write the data block
            //  replace_policy update
            //  set dirty
            PerfStats::get_instance().cache_access++;
            policy[index]->access(victim);
            way_metadata[index][victim]->write_access();
        } else {
            assert(write_allocate_type == No);
            //directly write it to memory
            PerfStats::get_instance().memory_access++;
        }
        
        return false;
    }
};

}; //namespace cache

#endif //CACHE_H_
