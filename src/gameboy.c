#include <stdio.h>
#include "cpu.h"

int main(int argc, int argv[])
{
    int i;
    cpu_t cpu;

    size_t size = 50;

    cpu.memory = alloc_memory(size);
    cpu.memory_start = cpu.memory;
    cpu.memory_size = (int)size;
    cpu.rom_filename = "test.gbc";

    // Fill with dummy values
    for (i = 0; i < size; i++, cpu.memory++) {
        *cpu.memory = i + 1;
    }

    // Run CPU
    run_cpu(&cpu);

    return 0;
}
