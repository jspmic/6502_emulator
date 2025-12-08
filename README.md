# 6502 Emulator

A small, self-contained emulator for the 6502 processor, written in C.
The design emphasizes clarity, modularity, and testability. It is intended for programmers who enjoy working close to the hardware and who appreciate the simplicity of the original 8-bit architecture.

The 6502 powered systems such as the NES, Commodore 64, and Apple II.
This project re-implements its behavior in a clean, inspectable form. This emulator is implemented for learning purposes only! Don't use it for a critical/serious project.

# Features

- Complete set of implemented 6502 instructions (with their addressing modes)

- Decentralized and modular source tree

- Per-instruction and per-addressing-mode tests

- Builds with GCC and Clang

Each instruction is defined together with its addressing mode.
This organization makes the code easy to follow and simplifies writing precise tests.

> Note: The layout will evolve. A dedicated `include/` directory for headers is planned.

# Testing
Instructions are tested individually along with their addressing modes. For example:

- `LDA_IM`: Load Accumulator, Immediate

- `STA_ZP`: Store Accumulator, Zero Page

Every legal opcode variant will eventually have its own test.
This fine granularity helps ensure correctness and simplifies debugging.

# Compiler Notes
The emulator uses compiler-specific initialization behavior:
```C
__attribute__((constructor)) void init(void)
{
    // initialization
}
```
Supported compilers:
- GCC
- Clang

# Building and Running
- Build: `make`
- Run: `./build/main`(only on Unix-like systems)
- Run tests: `make vtest`

# Contributing
Areas of interest include:
- Implementing remaining instructions
- Improving accuracy
- Expanding the test suite
- Refactoring subsystems as the project grows
- Writing a loader that loads the program into memory

Please send pull requests or open issues if you encounter problems or if you have a great idea.
