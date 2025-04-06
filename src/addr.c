#include "header.h"

void im(u32* cycles, CPU* cpu, Memory* mem, Byte** dst){
	Byte operand = fetch_byte(cycles, cpu, mem);
	*(*dst) = operand;
}
