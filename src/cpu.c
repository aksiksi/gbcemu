#include <stdio.h>
#include <time.h>
#include "cpu.h"
#include "instructions.h"

char *alloc_memory(size_t size)
{
    return (char *) calloc(size, sizeof(char));
}

void rewind_rom(cpu_t *cpu)
{
    cpu->rom = cpu->rom_start;
}

void init_cpu_registers(cpu_t *cpu)
{
    /* Set all internal registers of CPU to 0. */
    cpu->A = 0x00;
    cpu->F = 0x00;
    cpu->B = 0x00;
    cpu->C = 0x00;
    cpu->D = 0x00;
    cpu->E = 0x00;
    cpu->H = 0x00;
    cpu->L = 0x00;
    cpu->SP = 0xFFFE;
    cpu->PC = 0x0100;
    cpu->AF = 0x0000;
    cpu->BC = 0x0000;
    cpu->DE = 0x0000;
    cpu->HL = 0x0000;
}

void run_cpu(cpu_t *cpu)
{
    int i = 0;
    short current_opcode;

    // Initialize registers
    init_cpu_registers(cpu);

    // Load ROM into memory
    load_rom(cpu);
    
    // Show memory address range
    printf("\nFrom: %p -> To: %p\n", cpu->memory_start, cpu->memory + cpu->memory_size);

    // Show current address
    printf("Current: %p, Start: %p\n", cpu->memory, cpu->memory_start);

    // Play with registers
    cpu->A = 0x50;
    cpu->B = 0x20;
    cpu->SP = 0x43;
    cpu->H = 0x40;
    int AB = (cpu->A << 8) + cpu->B;

    printf("A = %x, B = %x, AB = %x, SP = %x\n", cpu->A, cpu->B, AB, cpu->SP);

    // Show ROM contents
    while (i < cpu->rom_size) {
        printf("Contents at %p: %x\n", cpu->rom, *cpu->rom);
        cpu->rom++;
        i++;
    }

    printf("ROM at: %p, %p, %x\n", cpu->rom, cpu->rom_start, *cpu->rom);

    rewind_rom(cpu);

    // Test register and memory values
    cpu->D = 0x0F;
    *(cpu->memory_start + cpu->HL) = 0x0F;

    // Loop through instructions
    while (cpu->rom != (cpu->rom_start + cpu->rom_size)) {
        current_opcode = *cpu->rom;
        interpret_instruction(cpu, current_opcode);
        printf("OPCODE: %x\n", current_opcode);
        cpu->rom++;
    }

    printf("A = %x\n", cpu->A);

    printf("ROM at: %p, %p, %x\n", cpu->rom, cpu->rom_start, *cpu->rom);

    // Free ALL memory once complete
    free(cpu->rom_start);
    free(cpu->memory_start);
}