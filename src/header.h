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
	INS_LDY_IM		= 0xA0,		// LDY Immediate
	INS_LDY_ZP		= 0xA4,		// LDY Zero Page
	INS_LDY_ZPX		= 0xB4,		// LDY Zero Page indeXed
	INS_LDY_AB		= 0xAC,		// LDY Absolute
	INS_LDY_ABX		= 0xBC,		// LDY Absolute indeXed

	INS_LDX_IM		= 0xA2,		// LDX Immediate
	INS_LDX_ZP		= 0xA6,		// LDX Zero Page
	INS_LDX_ZPY		= 0xB6,		// LDX Zero Page, Y
	INS_LDX_AB		= 0xAE,		// LDX Absolute
	INS_LDX_ABY		= 0xBE,		// LDX Absolute, Y

	INS_LDA_IM		= 0xA9,		// LDA Immediate
	INS_LDA_ZP		= 0xA5,		// LDA Zero Page
	INS_LDA_ZPX		= 0xB5,		// LDA Zero Page indeXed
	INS_LDA_AB		= 0xAD,		// LDA Absolute
	INS_LDA_ABX		= 0xBD,		// LDA Absolute indeXed
	INS_LDA_ABY		= 0xB9,		// LDA Absolute Y
	INS_LDA_INDX	= 0xA1,		// LDA Indexed Indirect
	INS_LDA_INDY	= 0xB1,		// LDA Indirect Y

	INS_STA_ZP		= 0x85,		// STA Zero Page
	INS_STA_ZPX		= 0x95,		// STA Zero Page indeXed
	INS_STA_INDX	= 0x81,		// STA Indexed Indirect
	INS_STA_INDY	= 0x91,		// STA Indirect Indexed

	INS_JSR			= 0x20,		// JSR
};

enum CYCLES{
	CCL_LD_IM 		= 2,		// Cycle for the LD<...> immediate mode instruction
	CCL_LD_ZP 		= 3,		// Cycle for the LD<...> Zero Page mode instruction
	CCL_LD_ZPX		= 4,		// Cycle for the LD<...> Zero Page indeXed mode instruction
	CCL_LD_ZPY		= 4,		// Cycle for the LD<...> Zero Page, Y mode instruction
	CCL_LD_AB		= 4,		// Cycle for the LD<...> Absolute mode instruction
	CCL_LD_ABX		= 5,		// Cycle for the LD<...> Absolute indeXed mode instruction
	CCL_LD_ABY		= 5,		// Cycle for the LD<...> Absolute, Y mode instruction
	CCL_LD_INDX		= 6,		// Cycle for the LD<...> Indexed Indirect mode instruction
	CCL_LD_INDY		= 6,		// Cycle for the LD<...> Indirect Indexed mode instruction

	CCL_ST_ZP 		= 3,		// Cycle for the ST<...> Zero Page mode instruction
	CCL_ST_ZPX		= 4,		// Cycle for the ST<...> Zero Page indeXed mode instruction
	CCL_ST_INDX		= 6,		// Cycle for the ST<...> Indexed Indirect mode instruction
	CCL_ST_INDY		= 6,		// Cycle for the ST<...> Indirect Indexed mode instruction

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
void zpy(u32* cycles, CPU* cpu, Memory* mem, Byte** dst);
void ab(u32* cycles, CPU* cpu, Memory* mem, Byte** dst);
void abx(u32* cycles, CPU* cpu, Memory* mem, Byte** dst);
void aby(u32* cycles, CPU* cpu, Memory* mem, Byte** dst);
void indX(u32* cycles, CPU* cpu, Memory* mem, Byte** dst);
void indY(u32* cycles, CPU* cpu, Memory* mem, Byte** dst);

void indX_st(u32* cycles, CPU* cpu, Memory* mem, Byte* src);
void indY_st(u32* cycles, CPU* cpu, Memory* mem, Byte* src);
void zp_st(u32* cycles, CPU* cpu, Memory* mem, Byte* src);
void zpx_st(u32* cycles, CPU* cpu, Memory* mem, Byte* src);

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
void write_byte(Byte value, u32 addr, u32 *cycles, Memory* mem);
void write_word(Word value, u32 addr, u32 *cycles, Memory* mem);
void execute(CPU* cpu, Memory* mem, u32 cycles);
void free_resource(CPU** cpu, Memory** mem);

#endif
