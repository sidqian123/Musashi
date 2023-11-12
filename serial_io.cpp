#include "serial_io.hpp"
#include <iostream>
#include <cstdio>

unsigned char SerialIO::read(unsigned int address) {
    // Implementation similar to the C version
    return 0xff;
}

void SerialIO::write(unsigned int address, unsigned char data) {
    char buffer[2] = {static_cast<char>(data), '\0'};
    switch (address) {
        case 0x51000000:
            append_to_string(port_A_data, data);
            if (data == '\n') {
                std::cout << "portA::" << port_A_data << std::endl;
            }
            break;
            // Similar cases for other addresses
        default:
            std::cerr << "temp error msg" << address << std::endl;
            exit(1);
    }
}

bool SerialIO::check(unsigned int address) {
    switch (address) {
        case 0x51000000:
        case 0x51000001:
        case 0x51000002:
        case 0x51000006:
            return true;
        default:
            return false;
    }
}

void SerialIO::append_to_string(std::string& str, char ch) {
    str.push_back(ch);
}
