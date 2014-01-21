#include <stdlib.h>
#include "instructions.h"

void split_opcode(short bytes[], short opcode)
{
    /* Split the opcode into upper and lower bytes using masking and shifting. */
    short mask;

    // Lower byte
    mask = 0x0F;
    bytes[0] = (opcode & mask);

    // Upper byte
    mask = 0xF0;
    bytes[1] = (opcode & mask) >> 4;
}

void load_rom(cpu_t *cpu)
{
    int c;
    FILE *fp;

    // ROM file handling
    fp = fopen(cpu->rom_filename, "rb");

    if (fp == NULL) {
        fprintf(stderr, "Cannot open file specified.\n");
        exit(0);
    }

    // Get ROM size
    int rom_size;
    fseek(fp, 0L, SEEK_END);
    rom_size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    // Allocate necessary memory for ROM then save into CPU
    cpu->rom = alloc_memory((size_t)rom_size);
    cpu->rom_start = cpu->rom;
    cpu->rom_size = rom_size;

    // Copy ROM contents into memory
    while ((c = fgetc(fp)) != EOF) {
        *cpu->rom = c;
        printf("Location: %p, Value: %x\n", cpu->rom, *cpu->rom);
        cpu->rom++;
    }

    // Rewind ROM pointer
    cpu->rom = cpu->rom_start;
}

void ld(cpu_t *cpu, short opcode)
{
    printf("Not implemented!\n");
}

void and(cpu_t *cpu, short opcode)
{
    short source;

    switch (opcode) {
        case 0xA0:
            source = cpu->B;
            break;
        case 0xA1:
            source = cpu->C;
            break;
        case 0xA2:
            source = cpu->D;
            break;
        case 0xA3:
            source = cpu->E;
            break;
        case 0xA4:
            source = cpu->H;
            break;
        case 0xA5:
            source = cpu->L;
            break;
        case 0xA6:
            source = *(cpu->memory_start + cpu->HL);
            break;
        case 0xA7:
            source = cpu->A;
            break;
    }

    printf("A = %x, S = %x -> ", cpu->A, source);

    cpu->A &= source;

    printf("A = %x\n", cpu->A);
}

void or(cpu_t *cpu, short opcode)
{
    short source;

    switch (opcode) {
        case 0xB0:
            source = cpu->B;
            break;
        case 0xB1:
            source = cpu->C;
            break;
        case 0xB2:
            source = cpu->D;
            break;
        case 0xB3:
            source = cpu->E;
            break;
        case 0xB4:
            source = cpu->H;
            break;
        case 0xB5:
            source = cpu->L;
            break;
        case 0xB6:
            source = *(cpu->memory_start + cpu->HL);
            break;
        case 0xB7:
            source = cpu->A;
            break;
    }

    printf("cpu.A = %x, Source = %x", cpu->A, source);

    cpu->A |= source;
}

void xor(cpu_t *cpu, short opcode)
{
	short source;

    switch (opcode) {
        case 0xA8:
            source = cpu->B;
            break;
        case 0xA9:
            source = cpu->C;
            break;
        case 0xAA:
            source = cpu->D;
            break;
        case 0xAB:
            source = cpu->E;
            break;
        case 0xAC:
            source = cpu->H;
            break;
        case 0xAD:
            source = cpu->L;
            break;
        case 0xAE:
            source = *(cpu->memory_start + cpu->HL);
            break;
        case 0xAF:
            source = cpu->A;
            break;
    }

    cpu->A ^= source;
}

void cp(cpu_t *cpu, short opcode)
{
    printf("Not implemented!\n");
}

void interpret_instruction(cpu_t *cpu, short opcode)
{
    // Split opcode into upper and lower bytes for easier use
    short bytes[2];
    split_opcode(bytes, opcode);
    printf("Whole: %x, Lower: %x, Upper: %x\n", opcode, bytes[0], bytes[1]);

    // Simple opcode interpreter
    switch (bytes[1]) {
        case 0xA:
            if (bytes[0] < 8)
                and(cpu, opcode);
            else
                xor(cpu, opcode);
            break;

        case 0xB:
            if (bytes[0] < 8)
                or(cpu, opcode);
            break;

        default:
            printf("Unknown opcode: %x\n", opcode);
            break;
    }
}
