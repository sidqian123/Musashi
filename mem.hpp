#ifndef MEMORY_MANAGER_HPP
#define MEMORY_MANAGER_HPP

#include <array>
#include <string>
#include <vector>

class Mem {
public:
    Mem();
    void load_section(const std::string& section_name, unsigned int address, unsigned int size);
    static const unsigned int MAX_ROM = 0xFFF;
    static const unsigned int MAX_RAM = 0xFFFFFF;
    static const unsigned int MAX_MEM = MAX_RAM + MAX_ROM;

    std::array<unsigned char, MAX_MEM + 1> g_mem{};
    std::array<unsigned char, 64> bootarg{};

    struct Section {
        std::string name;
        unsigned int address;
        unsigned int size;
    };

    std::vector<Section> sections;

    void init_sections();
};

#endif // MEMORY_MANAGER_HPP
