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

    /* Internal registers */
    char A; // Accumulator
    char F; // Flags = Z C H N 0 0 0 0
    short AF;
    
    char B; // GP
    char C; // Counter
    short BC;

    char D; // GP
    char E; // GP
    short DE;

    char H; // Pointer
    char L; // Pointer
    short HL;

    char SP; // Stack pointer
    char IP; // Instruction pointer
} cpu_t;

/* General functions */
char *alloc_memory(size_t size);
void run_cpu(cpu_t *cpu);
void init_cpu_registers(cpu_t *cpu);

#endif