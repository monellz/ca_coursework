#ifndef WAYMETADATA_H_
#define WAYMETADATA_H_

#include "bitset.h"
namespace cache {

//one way's metadata
template<unsigned TAG>
class WayMetadata {
public:
    virtual unsigned int get_tag() = 0;
    virtual void set_tag(unsigned int tag) = 0;

    void write_access() {};
    virtual bool is_valid() = 0;
    virtual void set_valid() = 0;
    virtual void set_invalid() = 0;

    //do someting when swap_out
    void before_swap_out(unsigned int new_tag) {}
};

template<unsigned TAG>
class WriteBack: public WayMetadata<TAG> {
private:
    // 0    |   1   | [2, metada.size)
    //valid | dirty | TAG
    Bitset<1 + 1 + TAG> metadata;
public:
    bool is_valid() { return metadata.test(0); }
    void set_valid() { metadata.set(0); }
    void set_invalid() { metadata.reset(0); }
    bool is_dirty() { return metadata.test(1); }
    void set_dirty() { metadata.set(1); }
    void clear_dirty() { metadata.reset(1); }

    unsigned int get_tag() {
        return metadata.range_get(2, metadata.size());
    }

    void set_tag(unsigned int tag) {
        return metadata.range_set(2, metadata.size(), tag);
    }

    void before_swap_out() {
        //should write back to memory?
        if (is_dirty()) {
            //write back 
        }
        clear_dirty();
    }

    void write_access() { set_dirty(); }
};

template<unsigned TAG>
class WriteThrough: public WayMetadata<TAG> {
private:
    // 0    | [1, metadata.size)
    //valid | TAG 
    Bitset<1 + TAG> metadata;
public:
    bool is_valid() { return metadata.test(0); }
    void set_valid() { metadata.set(0); }
    void set_invalid() { metadata.reset(0); }

    unsigned int get_tag() {
        return metadata.range_get(1, metadata.size());
    }
    void set_tag(unsigned int tag) {
        return metadata.range_set(1, metadata.size(), tag);
    }

};

}; //namespace cache
#endif //WAYMETADATA_H_
