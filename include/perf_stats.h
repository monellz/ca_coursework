#ifndef PERF_STATS_H_
#define PERF_STATS_H_

class PerfStats {
private:
    static PerfStats instance;
public:
    int memory_access;
    int cache_access;  //cache data block
    int total_access;
    int cache_miss;
    PerfStats() { clear(); }
    static PerfStats& get_instance() {
        return instance;
    }
    void clear() {
        memory_access = 0;
        cache_access = 0;
        total_access = 0;
        cache_miss = 0;
    }
};

#endif //PERF_STATS_H_
