#ifndef PERF_STATS_H_
#define PERF_STATS_H_

class PerfStats {
private:
    static PerfStats instance;
public:
    int memory_access;
    int cache_access;
    PerfStats(): memory_access(0), cache_access(0) {}
    static PerfStats& get_instance() {
        return instance;
    }
};

#endif //PERF_STATS_H_
