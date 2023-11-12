#ifndef SERIAL_IO_HPP
#define SERIAL_IO_HPP

#include <string>

class SerialIO {
public:
    unsigned char read(unsigned int address);
    void write(unsigned int address, unsigned char data);
    bool check(unsigned int address);

private:
    void append_to_string(std::string& str, char ch);
    std::string port_A_data, port_B_data, port_A_command, port_B_command;
};

#endif // SERIAL_IO_HPP
