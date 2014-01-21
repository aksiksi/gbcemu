#ifndef inst_seen
#define inst_seen

#include <stdio.h>
#include "cpu.h"

/* General functions */
void load_rom(cpu_t *cpu);
void interpret_instruction(cpu_t *cpu, short opcode);
static void split_opcode(short bytes[], short opcode);

/* Instruction set */
static void ld(cpu_t *cpu, short opcode); // Load
static void and(cpu_t *cpu, short opcode);
static void or(cpu_t *cpu, short opcode);
static void xor(cpu_t *cpu, short opcode);
static void cp(cpu_t *cpu, short opcode); // Compare

#endif