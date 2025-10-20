#include <unordered_map>
#include <string>
#include <algorithm>
#include <iostream>
#include <cstdint>
#include <vector>

std::unordered_map<std::string, uint32_t> lut;
std::vector<uintptr_t> addrs;

extern "C" {

int64_t get_ref(char *s) {
    std::string ss(s);
    std::unordered_map<std::string, uint32_t>::iterator it = lut.find(ss);
    if(it != lut.end()) {
        return it->second;
    }
    return -1;
}

void set_ref(char *s, uint32_t ref, uintptr_t addr) {
    std::string ss(s);
    lut[ss] = ref;
    addrs.push_back(addr);
}

char * ref_ptr(uint32_t ref) {
    return (char *)addrs[ref];
}

}