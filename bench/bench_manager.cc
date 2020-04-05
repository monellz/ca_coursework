#include "include/bench_manager.h"

using namespace bench;

BenchManager::BenchManager(): parser() {
    std::string dir = std::string(GLOBAL_PROJECT_DIR) + "/trace/";
    benches.resize(sizeof(TRACE)/sizeof(TRACE[0]));

    benches[0].name = std::string(TRACE[0]);
    benches[0].addr = dir + TRACE[0];
    parser.set_type(file::AccessType::ReadWrite);
    parser.parse(benches[0].addr, benches[0].access);

    benches[1].name = std::string(TRACE[1]);
    benches[1].addr = dir + TRACE[1];
    parser.set_type(file::AccessType::None);
    parser.parse(benches[1].addr, benches[1].access);

    benches[2].name = std::string(TRACE[2]);
    benches[2].addr = dir + TRACE[2];
    parser.set_type(file::AccessType::ReadWrite);
    parser.parse(benches[2].addr, benches[2].access);

    benches[3].name = std::string(TRACE[3]);
    benches[3].addr = dir + TRACE[3];
    parser.set_type(file::AccessType::None);
    parser.parse(benches[3].addr, benches[3].access);

    benches[4].name = std::string(TRACE[4]);
    benches[4].addr = dir + TRACE[4];
    parser.set_type(file::AccessType::LoadStore);
    parser.parse(benches[4].addr, benches[4].access);

    benches[5].name = std::string(TRACE[5]);
    benches[5].addr = dir + TRACE[5];
    parser.set_type(file::AccessType::ReadWrite);
    parser.parse(benches[5].addr, benches[5].access);

    benches[6].name = std::string(TRACE[6]);
    benches[6].addr = dir + TRACE[6];
    parser.set_type(file::AccessType::ReadWrite);
    parser.parse(benches[6].addr, benches[6].access);

    benches[7].name = std::string(TRACE[7]);
    benches[7].addr = dir + TRACE[7];
    parser.set_type(file::AccessType::None);
    parser.parse(benches[7].addr, benches[7].access);

    benches[8].name = std::string(TRACE[8]);
    benches[8].addr = dir + TRACE[8];
    parser.set_type(file::AccessType::LoadStore);
    parser.parse(benches[8].addr, benches[8].access);

    benches[9].name = std::string(TRACE[9]);
    benches[9].addr = dir + TRACE[9];
    parser.set_type(file::AccessType::LoadStore);
    parser.parse(benches[9].addr, benches[9].access);

}