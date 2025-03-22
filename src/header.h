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

// Opcodes
enum{
	INS_LDY_IM = 0xA0,
	INS_LDX_IM = 0xA2,
	INS_LDA_IM = 0xA9,
};

// Cycles
enum{
	CCL_LD_IM = 2,		// Cycle for the LD<...> immediate mode
};

extern void reset(CPU* cpu, Memory* mem);
extern void execute(CPU* cpu, Memory* mem, u32 cycles);

#endif
