GBCEmu
------

A fast and functional Gameboy Color emulator in C.

# Phase 1: Microprocessor

## Thoughts

We begin by defining what exactly our CPU needs to do in order to run Gameboy Color games. In simple terms, it needs to be able to take a ROM filled with machine code (0s and 1s), and execute the machine code instructions one by one.

How will the emulator interpret the machine code instructions? It will need to somehow convert the machine code into C and then execute that. For starters, we'll need to create a *disassembler* that translates each machine code instruction into a form of assembly. The instruction set of the GBC's CPU is thankfully quite simple when compared to today's CPUs. How simple? Well, to the point that there are no multiplication or division instructions!

The emulator could then run through the assembly instructions and execute them in C. So we may need an assembler as well - one that takes the raw assembly instructions and assembles them into a binary form runnable on modern x86 CPUs. Furthermore, all internal registers need to emulated as well so that they can be accessed.

What about the memory? That will definitely need to be emulated as well, since the incoming instructions from the ROM will need to access some sort of memory during execution. The size of the GBC's RAM is 64 kB and is well outlined in several documents put together by the emulation and RE scene in their early days. That could be done using an array of the given size perhaps.

I think the above should be enough to have rudimentary CPU emulation. Each component of the CPU could lie in its own header file, and each of these can then be accessed from a central `gameboy.c` that spins up a GBC instance on demand.

## Outline

The CPU logic will lie in two related files: `cpu.c` and `cpu.h`. A function, `run_cpu()`, will be the only function that the Gameboy (or any other external file) needs to invoke in order to spin up a CPU instance. `run_cpu()` will do something similar to the following:

1. Initialize the internal registers.
1. Allocate the necessary memory (RAM) for the device.
3. Setup the different sections in the memory and set default values if applicable.
4. Run a fetch-execute loop that takes one clock per iteration (not sure how this will be implemented).
5. On each iteration, the next instruction is fetched from the ROM, interpreted (ideas below), and then executed depending on its opcode.
6. At the end of the iteration, the sound and graphics output is updated (this will be worked on later).

The CPU itself will be represented by a standard struct. The struct will house a pointer to the memory, the internal registers, and the a pointer to the current instruction. It may also house the current state of the CPU (busy, free, off, etc.).

The ROM itself will be stored somewhere on disk, so the ROM location has to be provided (command line argument maybe), and then a `FILE` pointer will be setup to be able to work with it. Before processing, the ROM could maybe be copied into the RAM, but I doubt that this was the case with the Gameboy, as the ROM was provided on-cartridge and was usually larger in size. I'll have to check the specs for that.

Instructions will be fetched one by one from the ROM file, and then interpreted. The interpreter could be a simple function that takes the value and passes it to a static lookup table that contains all instructions. The C implementation of each instruction will basically be a function that takes a value as an argument (if applicable) and do something with it. I doubt any of them should return anything.

## CPU

The CPU is represented by a single `struct` called `cpu_t` (may be changed). For the time being, this `struct` contains pointers to the memory and the values of the internal registers. More may be added as development progresses.