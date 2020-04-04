#ifndef ADAPTIVE_INSERTION_POLICIES_H_
#define ADAPTIVE_INSERTION_POLICIES_H_

#include "replace_policy.h"

namespace cache {
//LRU Insertion Policy
template<unsigned WAY>
class LIP: public LRU<WAY> {
public:
    void access(int access_way) {
        //place all incoming lines to LRU position
        int w = this->stack_width();
        for (int i = 0; i < this->stack.size(); i += w) {
            if (this->stack.range_get(i, i + w) == access_way) {
                //found
                if (i + w >= this->stack.size()) {
                    //already in LRU
                    //move to MRU
                    for (i -= w; i >= 0; i -= w) {
                        this->stack.range_swap(i + w, i, w);
                    }
                } else {
                    //move to LRU
                    for (i += w; i < stack.size(); i += w) {
                        this->stack.range_swap(i - w, i, w);
                    }
                }
                break;
            }
        }
    }
};

/*
 *  Bimodal Insertion Policy
 * 
 *  P:  probability  parameter
 * 
 *  rand() % P == 0: place the incoming line to MRU position
 */ 
template<unsigned WAY, unsigned P = 2>
class BIP: public LRU<WAY> {
public:
    void access(int access_way) {
        int w = this->stack_width();
        for (int i = 0; i < this->stack.size(); i += w) {
            if (this->stack.range_get(i, i + w) == access_way) {
                //found
                if (rand() % P == 0) {
                    //move to MRU
                    for (i -= w; i >= 0; i -= w) {
                        this->stack.range_swap(i + w, i, w);
                    }
                } else {
                    //move to LRU
                    for (i += w; i < stack.size(); i += w) {
                        this->stack.range_swap(i - w, i, w);
                    }
                }
                break;
            }
        }
    }
};


}; //namespace cache


#endif //ADAPTIVE_INSERTION_POLICIES_H_