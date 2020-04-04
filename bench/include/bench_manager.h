#ifndef BENCH_MANAGER_H_
#define BENCH_MANAGER_H_

#include <iostream>
#include <string>
#include <vector>
#include "file_parser.h"
#include "global_build_config.h"

namespace bench {

struct Bench {
    std::string name;
    std::string addr;
    std::vector<cache::Access> access;
};

class BenchManager {
public:
    file::FileParser parser;
    std::vector<Bench> benches;
    BenchManager();
};

}; //namespace bench
#endif //BENCH_MANAGER_H_