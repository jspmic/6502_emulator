#ifndef GUARD
#define GUARD

#define MEM 1024*64
#define NO_INSTRUCTIONS 256

#define REG_A	65
#define REG_X	88
#define REG_Y	89

typedef unsigned char Byte;
typedef unsigned short Word;
typedef unsigned int u32;

typedef struct{
	Word data[MEM];
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
} CPU;

enum OPCODES{
	INS_LDY_IM		= 0xA0,

	INS_LDX_IM		= 0xA2,

	INS_LDA_IM		= 0xA9,		// LDA Immediate
	INS_LDA_ZP		= 0xA5,		// LDA Zero Page
	INS_LDA_ZPX		= 0xB5,		// LDA Zero Page indeXed
	INS_LDA_AB		= 0xAD,		// LDA Absolute
	INS_LDA_ABX		= 0xBD,		// LDA Absolute indeXed
	INS_LDA_ABY		= 0xB9,		// LDA Absolute Y
	INS_LDA_IDX		= 0xA1,		// LDA Indirect indeXed
	INS_LDA_IDY		= 0xB1,		// LDA Indirect Y

	INS_JSR			= 0x20,		// JSR
};

enum CYCLES{
	CCL_LD_IM 		= 2,		// Cycle for the LD<...> immediate mode instruction
	CCL_LD_ZP 		= 3,		// Cycle for the LD<...> Zero Page mode instruction
	CCL_LD_ZPX		= 4,		// Cycle for the LD<...> Zero Page indeXed mode instruction
	CCL_LD_AB		= 4,		// Cycle for the LD<...> Absolute mode instruction
	CCL_LD_ABX		= 5,		// Cycle for the LD<...> Absolute indeXed mode instruction
	CCL_JSR			= 6,		// Cycle for the JSR instruction
};

typedef void (*f_instruction)(u32*, CPU*, Memory*);

typedef struct{
	f_instruction functions[NO_INSTRUCTIONS];
	Byte init: 1;
} function_manager;

// Functions provided by addr.c
void im(u32* cycles, CPU* cpu, Memory* mem, Byte** dst);
void zp(u32* cycles, CPU* cpu, Memory* mem, Byte** dst);
void zpx(u32* cycles, CPU* cpu, Memory* mem, Byte** dst);
void ab(u32* cycles, CPU* cpu, Memory* mem, Byte** dst);
void abx(u32* cycles, CPU* cpu, Memory* mem, Byte** dst);

// Functions provided by instructions.c
void init(void);
void execute_instruction(Byte opcode, u32* cycles, CPU* cpu, Memory* mem);

// Functions provided by proc.c
void LDSet(CPU* cpu, u32 dst);
Byte read_without_pc(u32 *cycles, Word address, Memory* mem);
void reset(CPU* cpu, Memory* mem);
void free_resource(CPU** cpu, Memory** mem);
Byte fetch_byte(u32 *cycles, CPU* cpu, Memory* mem);
Word fetch_word(u32 *cycles, CPU* cpu, Memory* mem);
void write_word(Word value, u32 addr, u32 *cycles, Memory* mem);
void execute(CPU* cpu, Memory* mem, u32 cycles);
void free_resource(CPU** cpu, Memory** mem);

#endif
