#include "mem.hpp"
#include <fstream>
#include <iostream>
#include <cstdio>

Mem::Mem() {
    unsigned int text_section_address = 0x0000c000;
    g_mem[4] = (text_section_address >> 0) & 0xFF;
    g_mem[5] = (text_section_address >> 8) & 0xFF;
    g_mem[6] = (text_section_address >> 16) & 0xFF;
    g_mem[7] = (text_section_address >> 24) & 0xFF;
    init_sections();
}

void Mem::init_sections() {
    sections = {
            {"text", 0x0000c000, 0x001f5bfc},
            {"rodata", 0x00201c00, 0x0002f885},
            {"link_set_sysctl_funcs", 0x00231488, 0x000000c8},
            {"link_set_modules", 0x00231550, 0x00000108},
            {"link_set_domains", 0x00231658, 0x00000020},
            {"link_set_evcnts", 0x00231678, 0x00000048},
            {"link_set_dkwedge_methods", 0x002316c0, 0x00000004},
            {"link_set_prop_linkpools", 0x002316c4, 0x00000020},
            {"data", 0x00231740, 0x00016b8c},
            {"bss", 0x00248300, 0x00018858},
    };

    for (const auto& sec : sections) {
        load_section(sec.name, sec.address, sec.size);
    }
}

void Mem::load_section(const std::string& section_name, unsigned int address, unsigned int size) {
    std::string filepath = "./bins/" + section_name + ".bin";
    std::ifstream fhandle(filepath, std::ios::binary);

    if (!fhandle.is_open()) {
        std::cerr << "Unable to open " << filepath << std::endl;
        exit(1);
    }

    fhandle.read(reinterpret_cast<char*>(&g_mem[address]), size);
    fhandle.close();
}
