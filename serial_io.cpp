#include "serial_io.hpp"
#include <iostream>
#include <cstdio>

unsigned char SerialIO::read(unsigned int address) {
    return 0xff;
}

void SerialIO::write(unsigned int address, unsigned char data) {
    char buffer[10] = {static_cast<char>(data), '\0'}; // Convert data to string

    switch (address) {
        case 0x51000000: // Handling for port A data
            port_A_data_n++;
            append_to_string(port_A_data, buffer);
            if (data == '\n') {
                std::cout << "portA::" << port_A_data.substr(port_A_data_p) << std::endl;
                port_A_data_p = port_A_data_n;
            }
            break;

        case 0x51000001: // Handling for port B data
            port_B_data_n++;
            append_to_string(port_B_data, buffer);
            if (data == '\n') {
                std::cout << "portB::" << port_B_data.substr(port_B_data_p) << std::endl;
                port_B_data_p = port_B_data_n;
            }
            break;

        case 0x51000002: // Handling for port A command
            append_to_string(port_A_command, buffer);
            break;

        case 0x51000006: // Handling for port B command
            append_to_string(port_B_command, buffer);
            break;

        default: // Handling for unknown addresses
            std::cerr << "Unknown address in serial IO write: " << std::hex << address << std::endl;
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

void SerialIO::append_to_string(std::string& str, const char* buffer) {
    str.append(buffer);
}
