#include "obio_pio.hpp"
#include <iostream>

unsigned int ObioPio::read_port(unsigned int address) {
    switch (address) {
        case 0x49000000:
            std::cout << "Read OBIO_PIO0A\n";
            return OBIO_PIO0A;
            // Similar cases for other addresses
        default:
            std::cerr << "Invalid OBIO PIO port address " << address << std::endl;
            exit(1);
    }
}

void ObioPio::write_port(unsigned int address, unsigned int value) {
    switch (address) {
        case 0x49000000:
            OBIO_PIO0A = value;
            std::cout << "Write OBIO_PIO0A\n";
            break;
            // Similar cases for other addresses
        default:
            std::cerr << "Invalid OBIO PIO port address " << address << std::endl;
            exit(1);
    }
}

bool ObioPio::check_port(unsigned int address) {
    switch (address) {
        case 0x49000000:
        case 0x49000001:
        case 0x49000002:
        case 0x49000003:
            return true;
        default:
            return false;
    }
}
