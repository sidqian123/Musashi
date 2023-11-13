#ifndef SERIAL_IO_HPP
#define SERIAL_IO_HPP

#include <string>

class SerialIO {
public:
    unsigned char read(unsigned int address);
    void write(unsigned int address, unsigned char data);
    bool check(unsigned int address);

private:
    void append_to_string(std::string& str, const char* buffer);
    std::string port_A_data, port_B_data, port_A_command, port_B_command;
    size_t port_A_data_n = 0, port_A_data_p = 0;
    size_t port_B_data_n = 0, port_B_data_p = 0;
};

#endif // SERIAL_IO_HPP
