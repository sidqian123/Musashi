#include "cpu.hpp"
#include "m68k.h" // Include the Musashi library header

Cpu::Cpu() {
}

void Cpu::runCpu() {
    m68k_init();
    m68k_set_cpu_type(M68K_CPU_TYPE_68030);
    m68k_pulse_reset();
    while(true) {
        m68k_execute(100000);
    }
}
