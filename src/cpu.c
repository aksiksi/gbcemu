#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"

typedef struct {
	char *memory;
	char reg_a;
	char reg_b;
} Cpu;

char *allocate_memory(size_t size) {
	return (char *) calloc(size, sizeof(char));
}

int main(int argc, int argv[]) {
	Cpu cpu;

	cpu.memory = allocate_memory(10);
	cpu.reg_a = 0x08;
	cpu.reg_b = 0x09;

	char *memory = cpu.memory;
	int i;

	while (i < (int)sizeof(memory)) {
		printf("%d\n", *(memory++));
	}

	*memory = 0x10;
	printf("%d\n", *memory);

	*memory = 0x11;
	printf("%d\n", *(memory++));

	printf("%d\n", cpu.reg_a);

	// Free the memory
	free(cpu.memory);

	return 0;
}