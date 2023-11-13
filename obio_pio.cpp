#include "obio_pio.hpp"
#include <iostream>

unsigned int ObioPio::read_port(unsigned int address) {
    switch (address) {
        case 0x49000000:
            printf("Read OBIO_PIO0A\n");
            return OBIO_PIO0A;
        case 0x49000001:
            printf("Read OBIO_PIO0B\n");
            return OBIO_PIO0B;
        case 0x49000002:
            printf("Read OBIO_PIO0C\n");
            return OBIO_PIO0C;
        case 0x49000003:
            printf("Read OBIO_PIO0 Control\n");
            return OBIO_PIO0;
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
        case 0x49000001:
            OBIO_PIO0B = value;
            std::cout << "Write OBIO_PIO0B\n";
            break;
        case 0x49000002:
            printf("Write OBIO_PIO0C\n");
            OBIO_PIO0C = value;
            break;
        case 0x49000003:
            printf("Write OBIO_PIO0 Control\n");
            OBIO_PIO0 = value;
            break;
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
