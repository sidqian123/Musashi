#ifndef OBIO_PIO_HPP
#define OBIO_PIO_HPP

class ObioPio {
public:
    unsigned int read_port(unsigned int address);
    void write_port(unsigned int address, unsigned int value);
    bool check_port(unsigned int address);

private:
    unsigned int OBIO_PIO0A, OBIO_PIO0B, OBIO_PIO0C, OBIO_PIO0;
};

#endif // OBIO_PIO_HPP
