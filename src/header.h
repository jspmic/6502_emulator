#ifndef GUARD
#define GUARD

#include <stdio.h>
#include <stdint.h>

#define MEM ((1024*64)-1)
#define NO_INSTRUCTIONS 256
#define STACK_MAX 0x0100
#define STACK_MIN 0x01FF

#define REG_A	65
#define REG_X	88
#define REG_Y	89

// Processor status flags
#define C 1<<6
#define Z 1<<5
#define I 1<<4
#define D 1<<3
#define B 1<<2
#define O 1<<1
#define N 1<<0

typedef uint8_t Byte;
typedef uint16_t Word;
typedef uint32_t u32;

typedef struct{
	Word data[MEM];
	Byte init_true: 1;	// Check if memory is initialized
} Memory;

typedef struct{
	Word pc;	// Program counter(PC)
	Byte S;	// Stack pointer(SP)

	Byte a;		// Accumulator
	Byte x;		// Register X
	Byte y;		// Register Y

	Byte status;

	Byte init_true: 1;	// Check if cpu is initialized
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
	INS_STA_AB		= 0x8D,		// STA Absolute
	INS_STA_ABX		= 0x9D,		// STA Absolute, X
	INS_STA_ABY		= 0x99,		// STA Absolute, Y

	INS_JSR			= 0x20,		// JSR
	
	INS_CLC			= 0x18,		// CLC
	INS_SEC			= 0x38,		// SEC
	INS_NOP			= 0xEA,		// NOP
	INS_INY			= 0xC8,		// INY
	INS_INX			= 0xE8,		// INX
	
	INS_PHA			= 0x48,		// PHA: Push Accumulator
	INS_PHP			= 0x08,		// PHP: Push Processor Status
	INS_PLA			= 0x68,		// PLA: Pull Accumulator
	INS_PLP			= 0x28,		// PLP: Pull Processor Status
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

	CCL_ST_AB 		= 4,		// Cycle for the ST<...> Absolute mode instruction
	CCL_ST_ABX 		= 4,		// Cycle for the ST<...> Absolute, X mode instruction
	CCL_ST_ABY 		= 4,		// Cycle for the ST<...> Absolute, Y mode instruction
	CCL_ST_ZP 		= 3,		// Cycle for the ST<...> Zero Page mode instruction
	CCL_ST_ZPX		= 4,		// Cycle for the ST<...> Zero Page indeXed mode instruction
	CCL_ST_INDX		= 6,		// Cycle for the ST<...> Indexed Indirect mode instruction
	CCL_ST_INDY		= 6,		// Cycle for the ST<...> Indirect Indexed mode instruction

	CCL_JSR			= 6,		// Cycle for the JSR instruction

	CCL_CLC			= 2,		// Cycle for the CLC instruction
	CCL_SEC			= 2,		// Cycle for the SEC instruction
	CCL_NOP			= 2,		// Cycle for the NOP instruction
	CCL_INY			= 2,		// Cycle for the INY instruction
	CCL_INX			= 2,		// Cycle for the INX instruction

	CCL_PHX			= 3,		// Cycle for the PHX instruction
	CCL_PLX			= 4,		// Cycle for the PLX instruction
};

typedef void (*f_instruction)(u32*, CPU*, Memory*);

typedef struct{
	f_instruction functions[NO_INSTRUCTIONS];
	u32 cycles[NO_INSTRUCTIONS];
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
void ab_st(u32* cycles, CPU* cpu, Memory* mem, Byte* src);

void indX_st(u32* cycles, CPU* cpu, Memory* mem, Byte* src);
void indY_st(u32* cycles, CPU* cpu, Memory* mem, Byte* src);
void zp_st(u32* cycles, CPU* cpu, Memory* mem, Byte* src);
void zpx_st(u32* cycles, CPU* cpu, Memory* mem, Byte* src);

void push_stack(u32* cycles, CPU* cpu, Memory* mem, Byte data);
void pull_stack(u32* cycles, CPU* cpu, Memory* mem, Byte* dest);

// Functions provided by instructions.c
void init(void);
void execute_instruction(Byte opcode, u32* cycles, CPU* cpu, Memory* mem);
extern function_manager* manager;

// Functions provided by proc.c
void LDSet(CPU* cpu, u32 dst);
Byte read_without_pc(u32 *cycles, Word address, Memory* mem);
void reset(CPU* cpu, Memory* mem);
void free_resource(CPU** cpu, Memory** mem);
Byte fetch_byte(u32 *cycles, CPU* cpu, Memory* mem);
Word fetch_word(u32 *cycles, CPU* cpu, Memory* mem);
void write_byte(Byte value, u32 addr, u32 *cycles, Memory* mem);
void write_word(Word value, u32 addr, u32 *cycles, Memory* mem);
void execute(CPU* cpu, Memory* mem);
void free_resource(CPU** cpu, Memory** mem);
void print_memory(Memory* mem);
void set_status(CPU* cpu, unsigned int condition, uint8_t flag);
unsigned int get_status(CPU* cpu, uint8_t flag);

// Functions provided by loader.c
FILE* read_binary(const char* name);
void print_binary(FILE* fd);
void close_binary(FILE* fd);
void load_memory(FILE* fd, Memory* mem, CPU* cpu);

#endif
