#include <stdlib.h>
#include <stdio.h>
#include "../header.h"

FILE* read_binary(const char* name) {
		FILE* file = fopen(name, "rb");
		if (file == NULL) {
			perror("read_binary");
		}
		return file;
}

void print_binary(FILE* fd) {
	int c;
	while ((c = fgetc(fd)) != EOF) {
		printf("%.2X ", c);
	}
	printf("\n");
}

void load_memory(FILE* fd, Memory* mem, CPU* cpu) {
	int c;
	const Word _start_pc = cpu->pc;
	while ((c = fgetc(fd)) != EOF) {
		if ((int) cpu->pc > MEM) {
			perror("load_memory: memory full");
			return;
		}
		mem->data[cpu->pc] = (Word) c;
		cpu->pc++;
	}
	cpu->pc = _start_pc;
}

void close_binary(FILE* fd) {
	fclose(fd);
}
