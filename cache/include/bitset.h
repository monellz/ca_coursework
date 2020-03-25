#ifndef BITSET_H_
#define BITSET_H_

#include <cstdlib>
#include <assert.h>

template<unsigned int CHAR_NUM>
class Bitset {
private:
    char data[CHAR_NUM];
public:
    #define CHECK(x) {assert((x) < (CHAR_NUM << 3) && (x) >= 0);}
    Bitset() { memset(data, 0, sizeof(data)); }
    int size() {
        return CHAR_NUM << 3;
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
    bool test(int pos) {
        CHECK(pos);
        return data[pos >> 3] & (1 << (pos & 0x7));
    }
};

#endif //BITSET_H_
