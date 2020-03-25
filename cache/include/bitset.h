#ifndef BITSET_H_
#define BITSET_H_

#include <cstdlib>
#include <assert.h>

constexpr unsigned FLOOR_LOG2(unsigned x) {
    return x == 1? 0: FLOOR_LOG2(x >> 1) + 1;
}
constexpr unsigned CEIL_LOG2(unsigned x) {
    return x == 1? 0: FLOOR_LOG2(x - 1) + 1;
}

template<unsigned int BIT_NUM>
class Bitset {
private:
    char data[(BIT_NUM + 7) >> 3];
public:
    #define CHECK(x) {assert((x) < this->size() && (x) >= 0);}
    Bitset() {
        assert(BIT_NUM > 0);
        memset(data, 0, sizeof(data));
    }
    inline int size() {
        return BIT_NUM;
    }
    void reset(int pos = -1) {
        if (pos < 0) { memset(data, 0, sizeof(data)); }
        else {
            CHECK(pos);
            data[pos >> 3] &= ~(1 << (pos & 0x7));
        }
    }
    void set(int pos = -1) {
        if (pos < 0) { memset(data, -1, sizeof(data)); }
        else {
            CHECK(pos);
            data[pos >> 3] |= 1 << (pos & 0x7);
        }
    }
    void flip(int pos = -1) {
        if (pos < 0) {
            for (int i = 0; i < this->size(); ++i) {
                data[i >> 3] ^= 1 << (i & 0x7); 
            }
        } else {
            CHECK(pos);
            data[pos >> 3] ^= 1 << (pos & 0x7); 
        }
    }
    bool test(int pos) {
        CHECK(pos);
        return data[pos >> 3] & (1 << (pos & 0x7));
    }

    //TODO: better algorithm 
    void range_set(int s, int e, unsigned int v) {
        //set [s, e) to v  (from left to right)
        //v < 2^(e-s)        
        assert(v < (1 << (e - s)));
        for (int i = e - 1, j = 1; i >= s; --i, j <<= 1) {
            if (v & j) set(i);
            else reset(i);
        }
    }
    unsigned int range_get(int s, int e) {
        //get value at [s, e)
        assert(e > s);
        unsigned int ret = 0;
        for (int i = s, j = 1; i < e; ++i, j <<= 1) {
            if (test(i)) ret = (ret << 1) | 1;
            else ret <<= 1;
        }
        return ret;
    }

    void range_swap(int src_s, int dst_s, int width) {
        unsigned int src = range_get(src_s, src_s + width);
        unsigned int dst = range_get(dst_s, dst_s + width);
        range_set(src_s, src_s + width, dst);
        range_set(dst_s, dst_s + width, src);
    }
};
#endif //BITSET_H_
