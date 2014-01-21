#ifndef cpu_seen
#define cpu_seen

/* Includes */
#include <stdlib.h>

/* Structs */
typedef struct _cpu_t {
    /* Memory */
    char *memory;
    char *memory_start;
    int memory_size;

    /* ROM */
    char *rom;
    char *rom_start;
    char *rom_filename;
    int rom_size;

    /* Internal registers */
    short A; // Accumulator
    short F; // Flags = Z C H N 0 0 0 0
    short AF;

    short B; // GP
    short C; // Counter
    short BC;

    short D; // GP
    short E; // GP
    short DE;

    short H; // Pointer
    short L; // Pointer
    short HL;

    short SP; // Stack pointer
    short PC; // Instruction pointer
} cpu_t;

/* General functions */
char *alloc_memory(size_t size);
void run_cpu(cpu_t *cpu);
static void init_cpu_registers(cpu_t *cpu);

#endif