#include "cpu.hpp"
#include "mem.hpp"

int main(int argc, char* argv[]) {
    Mem mem;
    Cpu cpuEmulator;
    cpuEmulator.runCpu();
    return 0;
}
