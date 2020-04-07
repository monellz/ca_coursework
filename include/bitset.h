#ifndef BITSET_H_
#define BITSET_H_

#include <stdlib.h>
#include <string.h>
#include <assert.h>

constexpr unsigned FLOOR_LOG2(unsigned x) {
    return x == 1? 0: FLOOR_LOG2(x >> 1) + 1;
}
constexpr unsigned CEIL_LOG2(unsigned x) {
    return x == 1? 0: FLOOR_LOG2(x - 1) + 1;
}

template<unsigned BIT_NUM>
class Bitset {
private:
    unsigned char data[(BIT_NUM + 7) >> 3];
public:
    //#define CHECK(x) {assert((x) < this->size() && (x) >= 0);}
    #define CHECK(x) {}
    Bitset() {
        assert(BIT_NUM > 0);
        memset(data, 0, sizeof(data));
    }
    inline int size() {
        return BIT_NUM;
    }
    inline void reset(int pos = -1) {
        if (pos < 0) { memset(data, 0, sizeof(data)); }
        else {
            CHECK(pos);
            data[pos >> 3] &= ~(0x80 >> (pos & 0x7));
        }
    }
    inline void set(int pos = -1) {
        if (pos < 0) { memset(data, -1, sizeof(data)); }
        else {
            CHECK(pos);
            data[pos >> 3] |= (0x80 >> (pos & 0x7));
        }
    }
    inline void flip(int pos = -1) {
        if (pos < 0) {
            for (int i = 0; i < this->size(); ++i) {
                data[i >> 3] ^= (0x80 >> (i & 0x7)); 
            }
        } else {
            CHECK(pos);
            data[pos >> 3] ^= (0x80 >> (pos & 0x7)); 
        }
    }
    inline bool test(int pos) {
        CHECK(pos);
        return data[pos >> 3] & (0x80 >> (pos & 0x7));
    }

    inline void range_set(int s, int e, unsigned long long v) {
        //set [s, e) to v  (from left to right)
        //v < 2^(e-s)        
        //assert(e > s && s >= 0);
        //assert(v < (1ull << (e - s)));
        /*
        unsigned long long j = 1;
        for (int i = e - 1; i >= s; --i, j <<= 1) {
            if (v & j) set(i);
            else reset(i);
        }
        */

        #define left_mask(x) ((unsigned char)~((unsigned char)0xff >> (x)))
        #define right_mask(x) ((unsigned char)~((unsigned char)0xff << (x)))

        int ss = s >> 3;
        int ee = e >> 3;

        if (ss == ee) {
            unsigned char mask = left_mask(e & 0x7) & right_mask(8 - (s & 0x7));
            data[ee] = (data[ee] & (unsigned char)~mask) | (v << (8 - (e & 0x7)));
            return;
        }
        data[ee] = (unsigned char)((v & right_mask(e & 0x7)) << (8 - (e & 0x7))) + (data[ee] & right_mask(8 - (e & 0x7)));
        v >>= e & 0x7;
        for (int i = ee - 1; i >= ss + 1; i--) {
            data[i] = v & 0xff;
            v >>= 8; 
        }
        data[ss] = (data[ss] & left_mask(s & 0x7)) + (unsigned char)(v & right_mask(8 - (s & 0x7)));
    }
    inline unsigned long long range_get(int s, int e) {
        //get value at [s, e)
        //assert(e > s && s >= 0);
        unsigned long long ret = 0;
        int ss = s >> 3;
        int ee = e >> 3;
        ret += data[ss] & (~(0xff << (8 - (s & 0x7))));

        for (int i = ss + 1; i <= ee; ++i) {
            ret = (ret << 8) + data[i];
        }
        ret >>= (8 - (e & 0x7));
        return ret;
    }

    inline void range_swap(int src_s, int dst_s, int width) {
        unsigned long long src = range_get(src_s, src_s + width);
        unsigned long long dst = range_get(dst_s, dst_s + width);
        range_set(src_s, src_s + width, dst);
        range_set(dst_s, dst_s + width, src);
    }
};
#endif //BITSET_H_
