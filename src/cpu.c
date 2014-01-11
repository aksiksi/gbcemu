#include <stdio.h>
#include "cpu.h"

int test(int i) {
    return 42;
}

char *alloc_memory(size_t size) {
    return (char *) calloc(size, sizeof(char));
}

void init_cpu_registers(cpu_t *cpu) {
    /* Set all internal registers of CPU to 0. */
    cpu->A = 0x00;
    cpu->F = 0x00;
    cpu->B = 0x00;
    cpu->C = 0x00;
    cpu->D = 0x00;
    cpu->E = 0x00;
    cpu->H = 0x00;
    cpu->L = 0x00;
    cpu->SP = 0x00;
    cpu->IP = 0x00;
    cpu->AF = 0x0000;
    cpu->BC = 0x0000;
    cpu->DE = 0x0000;
    cpu->HL = 0x0000;
}

void run_cpu(cpu_t *cpu) {
    // Init registers
    init_cpu_registers(cpu);
    
    // Show memory address range
    printf("\nFrom: %p -> To: %p\n", cpu->memory_start, cpu->memory + cpu->memory_size);

    // Show current address
    printf("Current: %p, Start: %p\n", cpu->memory, cpu->memory_start);

    // Play with registers
    cpu->A = 0x40;
    cpu->B = 0x20;
    cpu->SP = 0x43;
    int AB = (cpu->A << 8) + cpu->B;

    printf("A = %x, B = %x, AB = %x, SP = %x\n", cpu->A, cpu->B, AB, cpu->SP);
}