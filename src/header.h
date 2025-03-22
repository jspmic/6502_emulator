#ifndef GUARD
#define GUARD

#define MEM 1024*64

typedef unsigned char Byte;
typedef unsigned short Word;
typedef unsigned int u32;

typedef struct{
	Byte data[MEM];
} Memory;

typedef struct{
	Word pc;	// Program counter(PC)
	Byte sp;	// Stack pointer(SP)

	Byte a;		// Accumulator
	Byte x;		// Register X
	Byte y;		// Register Y

	// These are parts of the Processor status
	// The processor status is 8-bits long
	// Each bit is a 1-bit flag
	Byte C: 1;	// Carry flag
	Byte Z: 1;	// Zero flag
	Byte I: 1;	// Interrupt disable flag
	Byte D: 1;	// Decimal mode flag
	Byte B: 1;	// Break command flag
	Byte O: 1;	// Overflow flag
	Byte N: 1;	// Negative flag
}__attribute__((packed)) CPU;

extern void reset(CPU* cpu, Memory* mem);

#endif
