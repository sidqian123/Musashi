#include "m68k.h"
#include "sim.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "c_compat.hpp"


#define MAX_ROM 0xfff                           /* Memory size for rom */
#define MAX_RAM 0xffffff                            /* Memory size for ram */
#define MAX_MEM (MAX_RAM)               /* ROM and RAM sizes */
#define MEMAVAIL_ADDRESS 0x4100000C              /* Memory availble address */
#define MEMAVAIL_VALUE_ADDRESS 0x41000010   /* Amount of memory configured */
#define PLANEMASK_ADDRESS 0x410000B8          /* Plane mask address */
#define PLANEMASK_VALUE_ADDRESS 0x410000C0    /* Plane mask value */
#define BOOTARG_ADDRESS 0x410000D4            /* Boot argument address */
#define BOOTARG_START 0x42000000                /* Boot argument start address */
#define BOOTARG_END (BOOTARG_START + 64 - 1)  /* Boot argument end address */

/* Read/write macros */
#define READ_8(BASE, ADDR) (BASE)[ADDR]
#define READ_16(BASE, ADDR) (((BASE)[ADDR] << 8) | (BASE)[(ADDR) + 1])
#define READ_32(BASE, ADDR) (                            \
    ((BASE)[ADDR] << 24) |                               \
    ((BASE)[(ADDR) + 1] << 16) |                         \
    ((BASE)[(ADDR) + 2] << 8) |                          \
    (BASE)[(ADDR) + 3]                                   \
)

#define WRITE_8(BASE, ADDR, VAL) (BASE)[ADDR] = (VAL)&0xff
#define WRITE_16(BASE, ADDR, VAL) do {                   \
    (BASE)[ADDR] = ((VAL) >> 8) & 0xff;                  \
    (BASE)[(ADDR) + 1] = (VAL) & 0xff;                   \
} while(0)
#define WRITE_32(BASE, ADDR, VAL) do {                   \
    (BASE)[ADDR] = ((VAL) >> 24) & 0xff;                 \
    (BASE)[(ADDR) + 1] = ((VAL) >> 16) & 0xff;           \
    (BASE)[(ADDR) + 2] = ((VAL) >> 8) & 0xff;            \
    (BASE)[(ADDR) + 3] = (VAL) & 0xff;                   \
} while(0)


/* Prototypes DO WE NEED THESE HERE? apg*/
void exit_error(char* fmt, ...);
unsigned int  m68k_read_memory_8(unsigned int address);
unsigned int  m68k_read_memory_16(unsigned int address);
unsigned int  m68k_read_memory_32(unsigned int address);
void m68k_write_memory_8(unsigned int address, unsigned int value);
void m68k_write_memory_16(unsigned int address, unsigned int value);
void m68k_write_memory_32(unsigned int address, unsigned int value);
void data_bus_recorder(const char *string, unsigned int address, unsigned int size);

/* initiallize memory array to 0 */
unsigned char g_mem[MAX_MEM+1] = {0};                 /* Memory in one array */
unsigned char bootarg[64] = {0};                            /* Boot argument */


/* struct definition */
struct section {
    const char* name;
    unsigned int address;
    unsigned int size;
};

/* track instruction execution */
void instruction_hook(unsigned int pc)
{
    printf("Now executing PC vvv: %08x\n", pc);
    if(pc == 70294)
    {
      printf("Starting pmap_kenter_pa()\n");
    }
}

/* Print the address and data bus */
void data_bus_recorder(const char *string, unsigned int address, unsigned int size) {
    if(address <= MAX_RAM)
        {
            printf("%s@RAM: %08x", string, address);

        if(size == 1)
        {
            printf(" value: %02x\n", (g_mem[address]) );
        }
        else if(size == 2)
        {
            printf(" value: %02x%02x\n", g_mem[address], g_mem[address+1] );
        }
        else if(size == 4)
        {
            printf(" value: %02x%02x%02x%02x\n", g_mem[address], g_mem[address+1], g_mem[address+2], g_mem[address+3]);
        }
    }
}

/* Exit with an error message.  Use printf syntax. */
void exit_error(char* fmt, ...)
{
    static int guard_val = 0;
    char buff[100];
    unsigned int pc;
    va_list args;

    if(guard_val)
        return;
    else
        guard_val = 1;

    /* FILE *out = stderr; */
    FILE *out = stdout;

    va_start(args, fmt);
    vfprintf(out, fmt, args);
    va_end(args);
    fprintf(out, "\n");
    pc = m68k_get_reg(NULL, M68K_REG_PPC);
    m68k_disassemble(buff, pc, M68K_CPU_TYPE_68000);
    fprintf(out, "At %04x: %s\n", pc, buff);

    exit(EXIT_FAILURE);
}



/* reads in 8 bits from memory array */
unsigned int m68k_read_memory_8(unsigned int address) {
    if(obio_pio_port_check(address)) return obio_pio_port(address);
    else if(serial_IO_check(address)) return serial_IO_read(address);
    else if (address >= MAX_MEM) {
        if (address >= BOOTARG_START && address <= BOOTARG_END) {
            return bootarg[address - BOOTARG_START];
        }
        exit_error("Attempted to read byte(read_8) from address %08x beyond memory size\n", address);
    }
    data_bus_recorder("m68k_read_memory_8", address, 1);
    return READ_8(g_mem, address);
}

/* reads in 16 bits from memory array */
unsigned int m68k_read_memory_16(unsigned int address) {
    if(obio_pio_port_check(address)) return obio_pio_port(address);
    else if(serial_IO_check(address))return serial_IO_read(address);
    else if (address >= MAX_MEM) {
        exit_error("Attempted to read byte(read_16) from address %08x beyond memory size\n", address);
    }
    data_bus_recorder("m68k_read_memory_16", address, 2);
    return READ_16(g_mem, address);
}

/* reads in 32 bits from memory array */
unsigned int m68k_read_memory_32(unsigned int address) {
    if(obio_pio_port_check(address)) return obio_pio_port(address);
    else if(serial_IO_check(address))return serial_IO_read(address);
    else if (address >= MAX_MEM) {
        if(address == MEMAVAIL_ADDRESS) {
            printf("Read 32 from MEMAVAIL_ADDRESS (%08x) value: %08x\n",MEMAVAIL_ADDRESS, MEMAVAIL_VALUE_ADDRESS);
            return MEMAVAIL_VALUE_ADDRESS;
        }
        else if(address == MEMAVAIL_VALUE_ADDRESS) {
            printf("Read 32 from MEMAVAIL_VALUE_ADDRESS (%08x) value: %08x\n", MEMAVAIL_VALUE_ADDRESS, MAX_MEM+1);
            return MAX_MEM+1;
        }
        else if(address == PLANEMASK_ADDRESS) {
            printf("Read 32 from PLANEMASK_ADDRESS (%08x) value: %08x\n", PLANEMASK_ADDRESS, PLANEMASK_VALUE_ADDRESS);
            return PLANEMASK_VALUE_ADDRESS;
        }
        else if(address == PLANEMASK_VALUE_ADDRESS) {
            printf("Read 32 from PLANEMASK_VALUE_ADDRESS (%08x) value: %08x\n", PLANEMASK_VALUE_ADDRESS, 0xff);
            return 0xff;
        }
        else if(address == BOOTARG_ADDRESS) {
            printf("Read 32 from BOOTARG_ADDRESS (%08x) value: %08x\n", BOOTARG_ADDRESS, BOOTARG_START);
            return BOOTARG_START;
        }
        else exit_error("Attempted to read byte(read_32) from address %08x beyond memory size\n", address);
    }
    data_bus_recorder("m68k_read_memory_32", address, 4);
    return READ_32(g_mem, address);
}

/* write in 8 bits to memory array */
void m68k_write_memory_8(unsigned int address, unsigned int value) {
    if(obio_pio_port_check(address)) {
        obio_pio_port_write(address, value);
        return;
    }
    else if(serial_IO_check(address)){
        serial_IO_write(address, value);
        return;
    }
    if (address > MAX_MEM) {
        exit_error("Attempted to write byte to address %08x beyond memory size\n", address);
    }
    // Check if the address is within the ROM range
    if (address <= MAX_ROM) {
        exit_error("Attempted to write byte to ROM address %08x", address);
    }
    WRITE_8(g_mem, address, value);
    data_bus_recorder("m68k_write_memory_8", address, 1);
}

/* write in 16 bits to memory array */
void m68k_write_memory_16(unsigned int address, unsigned int value) {
    if(obio_pio_port_check(address)) {
        obio_pio_port_write(address, value);
        return;
    }
    else if(serial_IO_check(address)){
        serial_IO_write(address, value);
        return;
    }
    if (address > MAX_MEM) {
        exit_error("Attempted to write byte to address %08x beyond memory size\n", address);
    }
    // Check if the address is within the ROM range
    if (address <= MAX_ROM) {
        exit_error("Attempted to write byte to ROM address %08x", address);
    }
    WRITE_16(g_mem, address, value);
    data_bus_recorder("m68k_write_memory_16", address, 2);
}

/* write in 32 bits to memory array */
void m68k_write_memory_32(unsigned int address, unsigned int value) {
    if(obio_pio_port_check(address)) {
        obio_pio_port_write(address, value);
        return;
    }
    else if(serial_IO_check(address)){
        serial_IO_write(address, value);
        return;
    }
    if (address > MAX_MEM) {
        exit_error("Attempted to write byte to address %08x beyond memory size\n", address);
    }
    // Check if the address is within the ROM range
    if (address <= MAX_ROM) {
        exit_error("Attempted to write byte to ROM address %08x", address);
    }
    WRITE_32(g_mem, address, value);
    data_bus_recorder("m68k_write_memory_32", address, 4);
}

unsigned int m68k_read_disassembler_16(unsigned int address)
{
    if(address > MAX_ROM)
        exit_error("Disassembler attempted to read word from ROM address %08x\n", address);
    return READ_16(g_mem, address);
}

unsigned int m68k_read_disassembler_32(unsigned int address)
{
    if(address > MAX_ROM){
        exit_error("Disassembler attempted to read long from ROM address %08x\n", address);
    }
    return READ_32(g_mem, address);
}

