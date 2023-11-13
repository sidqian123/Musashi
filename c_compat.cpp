#include "c_compat.hpp"
#include "serial_io.hpp"
#include "obio_pio.hpp"

static SerialIO serialIO;
static ObioPio obioPio;

unsigned char serial_IO_read(unsigned int address) {
    return serialIO.read(address);
}

void serial_IO_write(unsigned int address, unsigned char data) {
    serialIO.write(address, data);
}

int serial_IO_check(unsigned int address) {
    return serialIO.check(address) ? 1 : 0;
}

unsigned int obio_pio_port(unsigned int address) {
    return obioPio.read_port(address);
}

void obio_pio_port_write(unsigned int address, unsigned int value) {
    obioPio.write_port(address, value);
}

int obio_pio_port_check(unsigned int address) {
    return obioPio.check_port(address) ? 1 : 0;
}
void data_bus_recorder(const char *string, unsigned int address, unsigned int size){
    util.data_bus_recorder(string, address, size);
}
