#include "include/file_parser.h"
using namespace file;

FileParser::FileParser(AccessType type):access_type(type) {} 


bool FileParser::parse(const std::string& fn, std::vector<cache::Access>& access_list) {
    std::ifstream in(fn);
    if (!in.is_open()) return false;
    
    std::string data;
    while (in >> data) {
        cache::Access access;
        if (access_type != None) {
            if (!parse_type(data, access.type)) {
                in.close();
                return false;
            }
            in >> data;
        } else {
            //TODO
            access.type = cache::Read;
        }
        if (!parse_addr64(data, access.addr)) {
            in.close();
            return false;
        }
        access_list.push_back(access);
    }

    //std::cout << "total num: " << access_list.size() << std::endl;

    in.close();
    return true;
}


bool FileParser::parse_addr64(const std::string& src, uint64_t& dst) {
    dst = std::stoll(src);
    return true;
}

bool FileParser::parse_type(const std::string& src, cache::AccessType& dst) {
    if (access_type == ReadWrite) {
        if (src[0] == 'r') dst = cache::Read;
        else if (src[0] == 'w') dst = cache::Write;
        else return false;
    } else if (access_type == LoadStore) {
        if (src[0] == 'l') dst = cache::Read;
        else if (src[0] == 's') dst = cache::Write;
        else return false;
    } else if (access_type == None) {
        dst = cache::Read;
    } else {
        return false;
    }
    return true;
}
