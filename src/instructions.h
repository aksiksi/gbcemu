#ifndef inst_seen
#define inst_seen

#include <stdio.h>
#include "cpu.h"

/* General functions */
void load_rom(cpu_t *cpu);
void interpret_instruction(cpu_t *cpu, short opcode);
static void split_opcode(short *lower, short *upper, short opcode);

/* Instruction set */

/* Logic */
static void and(cpu_t *cpu, short opcode);
static void or(cpu_t *cpu, short opcode);
static void xor(cpu_t *cpu, short opcode);
static void cp(cpu_t *cpu, short opcode); // Compare

/* Data Movement */
static void ld_ir(cpu_t *cpu, short opcode); // Immediate to register
static void ld_rr(cpu_t *cpu, short opcode); // Register to register
static void ld_a(cpu_t *cpu, short opcode); // Load into A - immediate or register

/* Arithmetic */
static void add(cpu_t *cpu, short opcode);

#endif