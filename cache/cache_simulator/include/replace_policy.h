#ifndef REPLACE_POLICY_H_
#define REPLACE_POLICY_H_
#include "bitset.h"

namespace cache {
template<unsigned WAY>
class ReplacePolicy {
public:
    ReplacePolicy(){};
    virtual int victim_after_access(int access_way) = 0;
};

template<unsigned WAY>
class LRU: public ReplacePolicy<WAY> {
private:
    //left->top(newest),  right->bottom(oldest)
    Bitset<CEIL_LOG2(WAY) * WAY> stack;
public:
    LRU() {
        stack.reset();
        int w = stack_width();
        unsigned int way = 0;
        for (int i = 0; i < stack.size(); i += w) {
            stack.range_set(i, i + w, way);
            way++;
        }
        assert(way == WAY);
    }

    unsigned int stack_width() {
        return CEIL_LOG2(WAY);
    }

    int victim_after_access(int access_way) {
        int w = stack_width();
        for (int i = 0; i < stack.size(); i += w) {
            if (stack.range_get(i, i + w) == access_way) {
                //found
                //move to top
                for (i -= w; i >= 0; i -= w) {
                    stack.range_swap(i + w, i, w);
                }
                break;
            }
        }

        //the last one is the victim
        return stack.range_get(stack.size() - stack_width(), stack.size());
    }
};

template<unsigned WAY>
class BT: public ReplacePolicy<WAY> {
private:
    Bitset<WAY - 1> metadata;
public:
    BT() {
        metadata.reset();    
    }

    //left child
    #define lc(x) (((x) << 1) | 1)
    //right child
    #define rc(x) (((x) + 1) << 1)

    int victim_after_access(int access_way) {
        int i = 0;
        int p = i;
        while (lc(i) < metadata.size()) {
            p = i;
            if (metadata.test(i)) i = rc(i);
            else i = lc(i);
            metadata.flip(p);
        }

        if (metadata.test(i)) return rc(i) - metadata.size();
        else return lc(i) - metadata.size();
    }
};

}; //namespace cache
#endif //REPLACE_POLICY_H_
