#ifndef PERF_STATS_H_
#define PERF_STATS_H_

#include <fstream>
#include "bitset.h"

#define MAX_ACCESS_NUM 1000000

class PerfStats {
private:
    static PerfStats instance;
public:
    int memory_access;
    int cache_access;  //cache data block
    int total_access;
    int cache_miss;
    //0 hit, 1 miss
    Bitset<MAX_ACCESS_NUM> access_log;
    PerfStats(const PerfStats& p) = delete;
    PerfStats(PerfStats&& p) = delete;
    int time;

    //number of bit 1
    unsigned int bit_weight(unsigned long long n) {
        unsigned int res = 0;
        while (n) {
            n &= n - 1;
            res++;
        }
        return res;
    }


    PerfStats() { clear(); }
    static PerfStats& get_instance() {
        return instance;
    }
    void clear() {
        memory_access = 0;
        cache_access = 0;
        total_access = 0;
        cache_miss = 0;

        time = 0;
        access_log.reset();
        for (int i = 0; i < MAX_ACCESS_NUM; ++i) {
            assert(access_log.test(i) == false);
        }
    }

    void forward(bool hit) {
        if (!hit) {
            access_log.set(time);
            cache_miss++;
        }
        time++;
        total_access++;
    }

    unsigned int range_miss_num(int s, int e) {
        assert(s < time && e <= time);
        unsigned long long interval = access_log.range_get(s, e);
        return bit_weight(interval);
    }

    void log(const std::string& fn) {
        std::ofstream out(fn);
        for (int i = 0; i < time; ++i) {
            if (access_log.test(i)) out << "Miss" << std::endl;
            else out << "Hit" << std::endl;
        }
        out.close();
    }

};

#endif //PERF_STATS_H_
