#ifndef REPLACE_POLICY_H_
#define REPLACE_POLICY_H_
#include <iostream>
#include "bitset.h"
#include "perf_stats.h"

namespace cache {
template<unsigned WAY>
class ReplacePolicy {
public:
    ReplacePolicy(){};
    virtual void access(int access_way) {}
    virtual int victim() = 0;
    virtual void show() {}
};

template<unsigned WAY>
class LRU: public ReplacePolicy<WAY> {
public:
    //left->top(newest),  right->bottom(oldest)
    Bitset<CEIL_LOG2(WAY) * WAY> stack;


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

    inline unsigned int stack_width() {
        return CEIL_LOG2(WAY);
    }

    void access(int access_way) {
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
    }

    int victim() {
        //the last one is the victim
        return stack.range_get(stack.size() - stack_width(), stack.size());
    }

    void show() {
        for (int i = 0; i < stack.size(); i += stack_width()) {
            std::cout << stack.range_get(i, i + stack_width()) << "->";
        }
        std::cout << std::endl;
    }
};

template<unsigned WAY>
class BT: public ReplacePolicy<WAY> {
public:
    Bitset<WAY - 1> metadata;

    BT() {
        metadata.reset();    
    }

    //left child
    #define lc(x) (((x) << 1) | 1)
    //right child
    #define rc(x) (((x) + 1) << 1)

    int victim() {
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


template<unsigned WAY>
class FIFO: public LRU<WAY> {
public:
    void access(int access_way) {
        //do nothing
    }
    int victim() {
        //fifo
        int w = this->stack_width();
        for (int i = this->stack.size() - w; i >= w; i -= w) {
            this->stack.range_swap(i, i - w, w);
        }
        return this->stack.range_get(0, w); 
    }
};

template<unsigned WAY>
class Rand: public ReplacePolicy<WAY> {
public:
    int victim() {
        return rand() % WAY;
    }
};

}; //namespace cache
#endif //REPLACE_POLICY_H_
