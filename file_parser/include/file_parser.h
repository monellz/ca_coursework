#ifndef FILE_PARSER_H_
#define FILE_PARSER_H_

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include "cache_util.h"

namespace file {

enum AccessType {
    ReadWrite,
    LoadStore,
    None
};

class FileParser {
private:
    AccessType access_type;
public:
    FileParser(AccessType type = None);
    bool parse(const std::string& fn, std::vector<cache::Access>& access_list);
    bool parse_type(const std::string& src, cache::AccessType& dst);
    bool parse_addr64(const std::string& src, uint64_t& dst);
    void set_type(AccessType type);
};

} //namespace file

#endif //FILE_PARSER_H_
